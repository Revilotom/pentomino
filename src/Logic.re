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

[@react.component]
let make = () => {
  let (selected: option(shapeId), setSelectedHandler) =
    React.useState(() => None);
  let (shapeArray, setShapeArray) = React.useState(() => init);

  let placeShape = (id: shapeId, cell: int) =>
    setShapeArray(_ =>
      shapeArray
      |> Array.map(x => x.id === id ? {...x, cell: Some(cell)} : x)
    );

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
      deselect={_ => setSelectedHandler(_ => None)}
      placeShape
    />
    <div className="flex flex-wrap">
      <ShapeSelector
        selected
        setSelected={(id: shapeId) => setSelectedHandler(_ => Some(id))}
        shapeArray
      />
    </div>
  </div>;
};
