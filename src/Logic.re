open ShapeSelector;
// let colors: array(color) = [
//   Red,
//   Green,
//   Yellow,
//   Blue,
//   Orange,
//   Indigo,
//   Pink,
//   Purple,
// ];

let init: array(shape) =
  [|
    (<F />, Pink),
    (<I />, Red),
    (<L />, Blue),
    (<N />, Green),
    (<P />, Orange),
    (<V />, Indigo),
    (<W />, Purple),
    (<X />, Yellow),
    (<Y />, Teal),
  |]
  |> Array.mapi((i, (component, color)) =>
       {component, id: i, orientation: 0, cell: None, color}
     );

[@react.component]
let make = () => {
  let (selected, setSelectedHandler) = React.useState(() => None);
  let (shapeArray, setShapeArray) = React.useState(() => init);

  let placeShape = (id: int, cell: int) =>
    setShapeArray(_ =>
      shapeArray
      |> Array.map(x => x.id === id ? {...x, cell: Some(cell)} : x)
    );

  <div className="flex">
    <Grid
      selectedShape={selected->Belt.Option.map(i => shapeArray[i])}
      placedShapes={
        shapeArray->Belt.Array.keep(shape => shape.cell->Belt.Option.isSome)
      }
      placeShape
    />
    <div className="flex flex-wrap">
      <ShapeSelector
        selected
        setSelected={(num: int) => setSelectedHandler(_ => Some(num))}
        shapeArray
      />
    </div>
  </div>;
};
