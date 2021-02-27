open Jest;
open Solver;
open GridUtils;

open ShapeSelector;

open Constants;

open Belt_Array;

describe("Initial options", () => {
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
      let opts = getInitialOptions();
      let originalGrid = range(0, 63);

      let allPositions =
        getAllPositions(getInitialOptions(), originalGrid, centerCells);

      // Js.log(
      //   getInitialOptions()
      //   ->map(x => x.orientations)
      //   ->flatten
      //   ->map(showCoords)
      //   ->joinWith("\n\n", x => x),
      // );

      // let ucords =
      //   toCoords(Some(init[0]), 0, false)->map(c => addCoords(c, (0, 0)));

      // Js.log(ucords);
      // Js.log(ucords->map(coordsToindex)->map(indexToCoords));

      // Js.log(ucords->showCoords);

      // Js.log(allPositions);

      let s =
        allPositions
        ->map(x => x.orientations->map(showCoords)->joinWith("\n\n", x => x))
        ->joinWith("\n", x => x);

      Js.log(s);

      // Js.log(s
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
  );
});
