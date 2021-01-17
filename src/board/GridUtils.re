open ShapeSelector;

let toCoords = selectedShape =>
  switch (selectedShape) {
  | Some(selectedShape) =>
    switch (selectedShape.id) {
    | 0 => [|(1, 0), (0, 1), (1, 1), (2, 1), (0, 2)|]
    | 1 => [|(0, 0), (1, 0), (2, 0), (3, 0), (4, 0)|]
    | 2 => [|(0, 0), (1, 0), (1, 1), (1, 2), (1, 3)|]
    | 3 => [|(0, 0), (0, 1), (1, 1), (1, 2), (1, 3)|]
    | 4 => [|(0, 0), (1, 0), (2, 0), (0, 1), (1, 1)|]
    | 5 => [|(0, 2), (1, 2), (2, 2), (2, 0), (2, 1)|]
    | 6 => [|(0, 2), (1, 2), (1, 1), (2, 0), (2, 1)|]
    | 7 => [|(0, 1), (1, 0), (1, 1), (1, 2), (2, 1)|]
    | 8 => [|(0, 0), (0, 1), (0, 2), (0, 3), ((-1), 2)|]
    | _ => [||]
    }
  | None => [||]
  };

let indexToCoords = (index: int) => (index / 8, index mod 8);
let coordsToindex = ((x: int, y: int)) => x * 8 + y;

let addCoords = ((x1: int, y1: int), (x2: int, y2: int)) => (
  x1 + x2,
  y1 + y2,
);

let adjustCoords = (coords: array((int, int))) => {
  let max = (a, b) => a > b ? a : b;
  let min = (a, b) => a < b ? a : b;
  let maxX = coords->Belt.Array.reduce(-1, (acc, (x, y)) => max(x, acc));
  let minX = coords->Belt.Array.reduce(8, (acc, (x, y)) => min(x, acc));
  let maxY = coords->Belt.Array.reduce(-1, (acc, (x, y)) => max(y, acc));
  let minY = coords->Belt.Array.reduce(8, (acc, (x, y)) => min(y, acc));

  let yDiff = minY < 0 ? abs(minY) : maxY > 7 ? - (maxY - 7) : 0;
  let xDiff = minX < 0 ? abs(minX) : maxX > 7 ? - (maxX - 7) : 0;

  coords->Belt.Array.map(((x, y)) => (x + xDiff, y + yDiff));
};

let getRelativeIndexes =
    (relativeTo: option(int), coords: array((int, int))) =>
  relativeTo
  ->Belt.Option.map(pos =>
      coords
      |> Array.map(x => addCoords(x, indexToCoords(pos)))
      |> adjustCoords
      |> Array.map(coordsToindex)
    )
  ->Belt.Option.getWithDefault([||]);

let getPlacedShapeAtCell = (cell: int, placedShapes: array(shape)) => {
  placedShapes
  ->Belt.Array.keep(x =>
      getRelativeIndexes(x.cell, toCoords(Some(x)))
      ->Belt.Array.some(index => index === cell)
    )
  ->Belt.Array.get(0);
};
