open Jest;
open Solver;
open GridUtils;

describe("Initial options", () => {
  Expect.(
    test("toBe", () => {
      let opts = getInitialOptions();
      let originalGrid =
        Belt_Array.range(0, 63)
        ->Belt_Array.keep(x => !includes(centerCells, x));

      let allPositions = getAllPositions(getInitialOptions(), originalGrid);

      let gridToPrint =
        Belt_Array.range(0, 7)
        ->Belt_Array.map(row => Belt_Array.range(row * 8, (row + 1) * 8));

      // Js.log(allPositions);

      let s =
        allPositions
        ->Belt_Array.map(x =>
            x.orientations
            ->Belt_Array.map(coords =>
                gridToPrint
                ->Belt_Array.map(row =>
                    row
                    ->Belt_Array.map(cell =>
                        coords
                        ->Belt_Array.getBy(x => coordsToindex(x) === cell)
                        ->Belt_Option.isSome
                          ? "@" : " "
                      )
                    ->Belt_Array.joinWith("", x => x)
                  )
                ->Belt_Array.joinWith("\n", x => x)
              )
            ->Belt_Array.joinWith("\n", x => x)
          )
        ->Belt_Array.joinWith("\n", x => x);

      Js.log(s);

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
