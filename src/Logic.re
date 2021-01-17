open ShapeSelector;

let init: array(shape) =
  [|
    (<F />, Pink, F),
    (<I />, Red, I),
    (<L />, Blue, L),
    (<N />, Green, N),
    (<P />, Orange, P),
    (<V />, Indigo, V),
    (<W />, Purple, W),
    (<X />, Yellow, X),
    (<Y />, Teal, Y),
    (<Z />, Yellow, Z),
    (<U />, Indigo, U),
    (<T />, Blue, T),
  |]
  |> Array.map(((component, color, id)) =>
       {component, id, orientation: 0, cell: None, color}
     );

let document = Webapi.Dom.Document.asEventTarget(Webapi.Dom.document);

let keyToString = key =>
  switch (key) {
  | "s" => 180
  | "w" => 180
  | "d" => 90
  | "a" => (-90)
  | _ => 0
  };

let handleKey = e => Js.log(Dom.keyboardEvent.key(e));

[@react.component]
let make = () => {
  let (selected: option(shapeId), setSelectedHandler) =
    React.useState(() => None);
  let (shapeArray, setShapeArray) = React.useState(() => init);

  let placeShape = (id: option(shapeId), cell: option(int)) =>
    setShapeArray(_ =>
      shapeArray |> Array.map(x => Some(x.id) === id ? {...x, cell} : x)
    );

  let setSelected = (maybeId: option(shapeId)) =>
    setSelectedHandler(_ => maybeId);

  React.useEffect0(() => {
    Webapi.Dom.EventTarget.addEventListener("keypress", handleKey, document);
    /* clean up the subscription */
    Some(
      () =>
        Webapi.Dom.EventTarget.removeEventListener(
          "keypress",
          handleKey,
          document,
        ),
    );
  });

  <div className="flex">
    <Grid
      selectedShape={
        selected->Belt.Option.flatMap(id =>
          shapeArray->Belt.Array.getBy(shape => shape.id === id)
        )
      }
      placedShapes={
        shapeArray->Belt.Array.keep(shape => shape.cell->Belt.Option.isSome)
      }
      setSelected
      placeShape
    />
    <div className="flex flex-wrap">
      <ShapeSelector selected setSelected shapeArray />
    </div>
  </div>;
};
