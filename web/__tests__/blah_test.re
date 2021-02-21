open Jest;
open Solver;
open GridUtils;

describe("Initial options", () => {
  Expect.(
    test("toBe", () => {
      let opts = getInitialOptions();

      let allPositions =
        getAllPositions(
          getInitialOptions(),
          Belt_Array.range(0, 63)
          ->Belt_Array.keep(x => !includes(centerCells, x)),
        );

      // Js.log(allPositions);
      // Js.log(
      //   allPositions->Belt_Array.map(x =>
      //     x.orientations
      //     ->Belt_Array.map(coords => coords->Belt_Array.map(coordsToindex))
      //   ),
      // );

      Js.log(
        allPositions->Belt_Array.map(x => x.orientations->Belt_Array.length),
      );
      Js.log(
        allPositions
        ->Belt_Array.map(x => x.orientations->Belt_Array.length)
        ->Belt_Array.reduce(0, (acc, curr) => acc + curr),
      );

      expect(opts->Belt_Array.map(x => Belt_Array.length(x.orientations)))
      |> toEqual([|8, 2, 8, 8, 8, 4, 4, 1, 8, 4, 4, 4|]);
    })
  )
});
