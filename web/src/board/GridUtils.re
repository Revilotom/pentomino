open ShapeSelector;
open PairComparator;

let flip = ((x, y)) => (- x, y);

let rec applyRotation = ((x, y), rotation: int) =>
  switch (rotation) {
  | 0 => (x, y)
  | degress =>
    degress > 0
      ? applyRotation((y, - x), rotation - 90)
      : applyRotation((- y, x), rotation + 90)
  };

let addCoords = ((x1: int, y1: int), (x2: int, y2: int)) => {
  let xSum = x1 + x2;
  let ySum = y1 + y2;
  (xSum, ySum);
};

let toCoords =
    (selectedShape: option(shape), orientation: int, flipped: bool) =>
  (
    switch (selectedShape) {
    | Some(selectedShape) =>
      switch (selectedShape.id) {
      | F => [|(1, 0), (0, 1), (1, 1), (2, 1), (0, 2)|]
      | I => [|(0, 2), (1, 2), (2, 2), (3, 2), (4, 2)|]
      | L => [|(0, 0), (1, 0), (1, 1), (1, 2), (1, 3)|]
      | N => [|(0, 0), (0, 1), (1, 1), (1, 2), (1, 3)|]
      | P => [|(0, 1), (1, 1), (2, 1), (0, 2), (1, 2)|]
      | V => [|(0, 2), (1, 2), (2, 2), (2, 0), (2, 1)|]
      | W => [|(0, 2), (1, 2), (1, 1), (2, 0), (2, 1)|]
      | X => [|(0, 1), (1, 0), (1, 1), (1, 2), (2, 1)|]
      | Y => [|(2, 0), (2, 1), (2, 2), (2, 3), (1, 2)|]
      | T => [|(0, 0), (0, 1), (0, 2), (1, 1), (0, 1)|]
      | U => [|(0, 0), (1, 0), (1, 1), (1, 2), (0, 2)|]
      | Z => [|(0, 0), (0, 1), (1, 1), (2, 1), (2, 2)|]
      }
    | None => [||]
    }
  )
  |> (
    arr =>
      arr
      |> Array.map(coord => flipped ? flip(coord) : coord)
      |> Array.map(coord => applyRotation(coord, orientation))
  );

let indexToCoords = (index: int) => (index / 8, index mod 8);

let coordsToindex = ((x: int, y: int)) => x * 8 + y;

let coordsToString = ((x: int, y: int)) =>
  "(" ++ string_of_int(x) ++ "," ++ string_of_int(y) ++ ")";

let centerCells =
  [|(3, 3), (4, 3), (3, 4), (4, 4)|]->Belt.Array.map(coordsToindex);

let max = (a, b) => a > b ? a : b;
let min = (a, b) => a < b ? a : b;

let adjustCoords = (coords: array((int, int))) => {
  let maxX = coords->Belt.Array.reduce(-1, (acc, (x, _)) => max(x, acc));
  let minX = coords->Belt.Array.reduce(8, (acc, (x, _)) => min(x, acc));
  let maxY = coords->Belt.Array.reduce(-1, (acc, (_, y)) => max(y, acc));
  let minY = coords->Belt.Array.reduce(8, (acc, (_, y)) => min(y, acc));

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
  ->Belt.Array.keep(placedShape =>
      getRelativeIndexes(
        placedShape.cell,
        toCoords(
          Some(placedShape),
          placedShape.orientation,
          placedShape.flipped,
        ),
      )
      ->Belt.Array.some(index => index === cell)
    )
  ->Belt.Array.get(0);
};

let hasDuplicates = (arr: array(int)) =>
  Belt.Set.Int.fromArray(arr) |> Belt.Set.Int.size !== Array.length(arr);

let includes = (arr, element) => arr->Belt.Array.some(x => x === element);

let flatten = arr =>
  arr->Belt.Array.reduce([||], (acc, curr) => Belt.Array.concat(acc, curr));
