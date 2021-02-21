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

let shapeToString = s =>
  switch (s) {
  | F => "F"
  | I => "I"
  | L => "L"
  | N => "N"
  | P => "P"
  | T => "T"
  | U => "U"
  | V => "V"
  | W => "W"
  | X => "X"
  | Y => "Y"
  | Z => "Z"
  };

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
  component: React.element,
  cell: option(int),
  color,
  orientation: int,
  flipped: bool,
};

type shapeState =
  | Placed
  | Available
  | Selected;

let shapeToShapeState = (shape, selected, placedShapes) => {
  let placedOrAvailable =
    placedShapes
    ->Belt.Array.getBy(pS => pS.id === shape.id)
    ->Belt.Option.isSome
      ? Placed : Available;

  switch (selected) {
  | Some(id) => id === shape.id ? Selected : placedOrAvailable
  | None => placedOrAvailable
  };
};

[@react.component]
let make =
    (
      ~setSelected,
      ~selected,
      ~shapeArray: array(shape),
      ~placedShapes: array(shape),
    ) => {
  <>
    {shapeArray
     |> Array.mapi((i, shape) => {
          let state = shapeToShapeState(shape, selected, placedShapes);

          <div
            key={string_of_int(i)}
            className={
              switch (state) {
              | Selected => " text-yellow-300"
              | Available => "text-blue-200"
              | Placed => "text-gray-500"
              }
            }
            onClick={_ =>
              switch (state) {
              | Selected => setSelected(None)
              | Available => setSelected(Some(shape.id))
              | Placed => setSelected(None)
              }
            }>
            {shape.component}
          </div>;
        })
     |> React.array}
  </>;
};
