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
       {component, id, orientation: 0, flipped: false, cell: None, color}
     );

let keyToOrientation = key =>
  switch (key) {
  | "d" => 90
  | "a" => (-90)
  | _ => 0
  };

[@react.component]
let make = () => {
  let (selected: option(shapeId), setSelectedHandler) =
    React.useState(() => None);
  let (shapeArray, setShapeArray) = React.useState(() => init);

  let (orientation: int, setOrientation) = React.useState(() => 0);
  let (flipped: bool, setFlipped) = React.useState(() => false);

  let handleKey = e => {
    let key = Webapi.Dom.KeyboardEvent.key(e);
    let diff = key |> keyToOrientation;
    setOrientation(prevOrientation => (diff + prevOrientation) mod 360);
    if (key === "w" || key == "s") {
      setFlipped(prevFlipped => !prevFlipped);
    };
  };
  Js.log(orientation);

  let placeShape = (id: option(shapeId), cell: option(int)) =>
    setShapeArray(_ =>
      shapeArray
      |> Array.map(x =>
           Some(x.id) === id ? {...x, cell, orientation, flipped} : x
         )
    );

  let setSelected = (maybeId: option(shapeId)) =>
    setSelectedHandler(_ => maybeId);

  React.useEffect0(() => {
    Webapi.Dom.Document.addKeyDownEventListener(
      handleKey,
      Webapi.Dom.document,
    );
    Some(
      () =>
        Webapi.Dom.Document.removeKeyDownEventListener(
          handleKey,
          Webapi.Dom.document,
        ),
    );
  });

  <div className="flex">
    <Grid
      flipped
      orientation
      resetOrientation={_ => {
        setOrientation(_ => 0);
        setFlipped(_ => false);
      }}
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
