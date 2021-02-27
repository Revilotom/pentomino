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
    test("add coords y overflow", () => {
      expect(addCoords((0, 7), (0, 1))) |> toEqual((1, 0))
    })
  );

  Expect.(
    test("add coords x overflow", () => {
      expect(addCoords((7, 0), (1, 0))) |> toEqual((0, 0))
    })
  );

  Expect.(
    test("toBe", () => {
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

  Expect.(test("toBe", () => {
            expect(totalPlaces) |> toEqual(1568)
          }));

  Expect.(
    test("toBe", () => {
      let s =
        allPositions
        ->map(x => x.orientations->map(showCoords)->joinWith("\n\n", x => x))
        ->joinWith("\n", x => x);

      // Js.log(s);

      // Js.log(
      //   opts
      //   ->map(x => x.orientations->map(showCoords)->joinWith("\n\n", x => x))
      //   ->joinWith("\n", x => x),
      // );

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
         |]);
    })
  );
});
