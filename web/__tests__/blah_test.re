open Jest;
open Solver;
open GridUtils;

open ShapeSelector;

open Belt_Array;

describe("Initial options", () => {
  Expect.(
    test("toBe", () => {
      let opts = getInitialOptions();
      let originalGrid = range(0, 63)->keep(x => !includes(centerCells, x));

      let allPositions = getAllPositions(getInitialOptions(), originalGrid);

      Js.log(allPositions);

      let s =
        allPositions
        ->map(x => x.orientations->map(showCoords)->joinWith("\n\n", x => x))
        ->joinWith("\n", x => x);

      // Js.log(s);
      // Js.log(
      //   allPositions->map(x =>
      //     x.orientations->map(y => y->map(z => z->coordsToString))
      //   ),
      // );

      Js.log(
        allPositions->map(x =>
          (shapeToString(x.shapeId), x.orientations->length)
        ),
      );

      Js.log(
        allPositions
        ->map(x => x.orientations->length)
        ->reduce(0, (acc, curr) => acc + curr),
      );

      expect(opts->map(x => length(x.orientations)))
      |> toEqual([|8, 2, 8, 8, 8, 4, 4, 1, 8, 4, 4, 4|]);
    })
  )
});
