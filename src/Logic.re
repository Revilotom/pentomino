open ShapeSelector;

let shapeArray: array(shape) =
  [|<F />, <I />, <L />, <N />, <P />, <V />, <W />, <X />, <Y />|]
  |> Array.mapi((i, x) => {component: x, id: i, orientation: 0});

[@react.component]
let make = () => {
  let (selected, setSelectedHandler) = React.useState(() => None);
  let grid = Array.create(64, None);

  Js.log(selected);

  <div className="flex">
    <Grid />
    <div className="flex flex-wrap">
      <ShapeSelector
        selected
        setSelected={(num: int) => setSelectedHandler(_ => Some(num))}
        shapeArray
      />
    </div>
  </div>;
};
