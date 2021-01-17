type shapeId =
  | F
  | I
  | L
  | N
  | P
  | T
  | U
  | V
  | W
  | X
  | Y
  | Z;

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

let colorToString = (c: color) =>
  switch (c) {
  | Red => "red"
  | Indigo => "indigo"
  | Orange => "orange"
  | Green => "green"
  | Yellow => "yellow"
  | Purple => "purple"
  | Blue => "blue"
  | Pink => "pink"
  | Teal => "teal"
  };

type shape = {
  id: shapeId,
  orientation: int,
  component: React.element,
  cell: option(int),
  color,
};

[@react.component]
let make = (~setSelected, ~selected, ~shapeArray: array(shape)) => {
  <>
    {shapeArray
     |> Array.mapi((i, x) =>
          <div
            key={string_of_int(i)}
            className={
              "p-5 "
              ++ (selected === Some(x.id) ? "text-red-600" : "text-blue-500 ")
            }
            onClick={_ => setSelected(x.id)}>
            {x.component}
          </div>
        )
     |> React.array}
  </>;
};
