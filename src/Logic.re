open ShapeSelector;

let init: array(shape) =
  [|<F />, <I />, <L />, <N />, <P />, <V />, <W />, <X />, <Y />|]
  |> Array.mapi((i, x) => {component: x, id: i, orientation: 0, cell: None});

[@react.component]
let make = () => {
  let (selected, setSelectedHandler) = React.useState(() => None);
  let (shapeArray, setShapeArray) = React.useState(() => init);

  let placeShape = (id: int, cell: int) =>
    setShapeArray(_ =>
      shapeArray
      |> Array.map(x => x.id === id ? {...x, cell: Some(cell)} : x)
    );

  let grid = Array.make(64, None);

  Js.log(selected);
  Js.log(shapeArray);

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
