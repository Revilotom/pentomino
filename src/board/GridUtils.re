open ShapeSelector;

let flip = ((x, y)) => (- x, - y);

let rec applyRotation = ((x, y), rotation: int) =>
  switch (rotation) {
  | 0 => (x, y)
  | degress =>
    degress > 0
      ? applyRotation((y, - x), rotation - 90)
      : applyRotation((- y, x), rotation + 90)
  };

let addCoords = ((x1: int, y1: int), (x2: int, y2: int)) => (
  x1 + x2,
  y1 + y2,
);

let toCoords =
    (selectedShape: option(shape), orientation: int, flipped: bool) =>
  (
    switch (selectedShape) {
    | Some(selectedShape) =>
      switch (selectedShape.id) {
      | F => ([|(1, 0), (0, 1), (1, 1), (2, 1), (0, 2)|], ((-1), (-1)))
      | I => ([|(0, 0), (1, 0), (2, 0), (3, 0), (4, 0)|], ((-2), 0))
      | L => ([|(0, 0), (1, 0), (1, 1), (1, 2), (1, 3)|], ((-1), (-1)))
      | N => ([|(0, 0), (0, 1), (1, 1), (1, 2), (1, 3)|], ((-1), (-1)))
      | P => ([|(0, 0), (1, 0), (2, 0), (0, 1), (1, 1)|], ((-1), 0))
      | V => ([|(0, 2), (1, 2), (2, 2), (2, 0), (2, 1)|], ((-2), (-2)))
      | W => ([|(0, 2), (1, 2), (1, 1), (2, 0), (2, 1)|], ((-1), (-1)))
      | X => ([|(0, 1), (1, 0), (1, 1), (1, 2), (2, 1)|], ((-1), (-1)))
      | Y => ([|(0, 0), (0, 1), (0, 2), (0, 3), ((-1), 2)|], (0, (-2)))
      | T => ([|(0, 0), (0, 1), (0, 2), (1, 1), (2, 1)|], ((-1), (-1)))
      | U => ([|(0, 0), (1, 0), (1, 1), (1, 2), (0, 2)|], ((-1), (-1)))
      | Z => ([|(0, 0), (0, 1), (1, 1), (2, 1), (2, 2)|], ((-1), (-1)))
      }
    | None => ([||], (0, 0))
    }
  )
  |> (
    ((arr, translation)) =>
      arr
      |> Array.map(coord => addCoords(translation, coord))
      |> Array.map(coord => applyRotation(coord, orientation))
      |> Array.map(coord => flipped ? flip(coord) : coord)
  );

let indexToCoords = (index: int) => (index / 8, index mod 8);
let coordsToindex = ((x: int, y: int)) => x * 8 + y;

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
