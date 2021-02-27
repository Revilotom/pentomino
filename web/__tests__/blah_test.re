open Jest;
open Solver;
open GridUtils;

open ShapeSelector;

open Constants;

open Belt_Array;

describe("Initial options", () => {
  let opts = getInitialOptions();

  let allPositions = getAllPositions(opts, range(0, 63), centerCells);

  let shapesToPlaces =
    allPositions->map(x =>
      (shapeToString(x.shapeId), x.orientations->length)
    );

  let totalPlaces =
    allPositions
    ->map(x => x.orientations->length)
    ->reduce(0, (acc, curr) => acc + curr);

  Expect.(
    test("orientations", () => {
      expect(
        opts->map(x => (shapeToString(x.shapeId), length(x.orientations))),
      )
      |> toEqual([|
           ("F", 8),
           ("I", 2),
           ("L", 8),
           ("N", 8),
           ("P", 8),
           ("V", 4),
           ("W", 4),
           ("X", 1),
           ("Y", 8),
           ("Z", 4),
           ("U", 4),
           ("T", 4),
         |])
    })
  );

  Expect.(
    test("places", () => {
      expect(shapesToPlaces)
      |> toEqual([|
           ("F", 192),
           ("I", 48),
           ("L", 184),
           ("N", 184),
           ("P", 248),
           ("V", 96),
           ("W", 96),
           ("X", 24),
           ("Y", 184),
           ("Z", 96),
           ("U", 120),
           ("T", 96),
         |])
    })
  );

  Expect.(
    test("total places", () => {
      expect(totalPlaces) |> toEqual(1568)
    })
  );
});
