open ShapeSelector;

let toCoords = selectedShape =>
  switch (selectedShape) {
  | Some(selectedShape) =>
    switch (selectedShape.id) {
    | 0 => [|(0, 1), (1, 0), (1, 1), (1, 2), (2, 0)|]
    | 1 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
    | 2 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
    | 3 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
    | 4 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
    | 5 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
    | 6 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
    | 7 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
    | 8 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
    | _ => [||]
    }
  | None => [||]
  };

let isValid = coords =>
  coords->Belt.Array.keep(((x, y)) => x >= 0 && x <= 7 && y >= 0 && y <= 7)
  |> Array.length === Array.length(coords);

let indexToCoords = (index: int) => (index / 8, index mod 8);
let coordsToindex = ((x: int, y: int)) => x * 8 + y;

let addCoords = ((x1: int, y1: int), (x2: int, y2: int)) => (
  x1 + x2,
  y1 + y2,
);

[@react.component]
let make = (~selectedShape: option(shape)) => {
  let (mousePos, setMousePos) = React.useState(() => None);

  let coords = toCoords(selectedShape);
  // Js.log(mousePos);
  // Js.log(coords);
  // Js.log(
  //   mousePos
  //   ->Belt.Option.map(pos =>
  //       coords |> Array.map(x => addCoords(x, indexToCoords(pos)))
  //     )
  //   ->Belt.Option.getWithDefault([||]),
  // );
  // Js.log(mousePos->Belt.Option.map(indexToCoords));
  // Js.log(
  //   mousePos->Belt.Option.map(indexToCoords)->Belt.Option.map(coordsToindex),
  // );

  let relativeIndexes: array(int) =
    mousePos
    ->Belt.Option.map(pos =>
        coords
        |> Array.map(x => addCoords(x, indexToCoords(pos)))
        |> Array.map(coordsToindex)
      )
    ->Belt.Option.getWithDefault([||]);

  Js.log(relativeIndexes);

  <div className="flex justify-items-auto justify-center">
    <div
      className="justify-center h-full flex flex-wrap content-start  "
      style={ReactDOM.Style.make(~width="700px", ())}>
      {Array.make(64, None)
       |> Array.mapi((i, _) =>
            <Cell
              highlight={relativeIndexes->Belt.Array.some(x => x == i)}
              index={Some(i)}
              setPos={x => setMousePos(_ => x)}
              key={string_of_int(i)}
            />
          )
       |> React.array}
    </div>
  </div>;
};
