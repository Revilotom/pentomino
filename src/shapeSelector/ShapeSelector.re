type color =
  | Red
  | Indigo
  | Orange
  | Green
  | Yellow
  | Purple
  | Blue
  | Pink
  | Teal;

type shape = {
  id: int,
  orientation: int,
  component: React.element,
  cell: option(int),
  color,
};

[@react.component]
let make = (~setSelected, ~selected, ~shapeArray: array(shape)) => {
  <>
    {shapeArray
     |> Array.map(x =>
          <div
            key={string_of_int(x.id)}
            className={
              "p-5 "
              ++ (
                selected === Some(x.id) ? "text-red-600" : "text-blue-500 bg-"
              )
            }
            onClick={_ => setSelected(x.id)}>
            {x.component}
          </div>
        )
     |> React.array}
  </>;
};
