open Jest;
open Solver;
open GridUtils;

describe("Initial options", () => {
  Expect.(
    test("toBe", () =>
      expect(
        getInitialOptions()->Belt_Array.map(x => Belt_Array.length(x.cells)),
      )
      |> toEqual([|8, 2, 8, 8, 8, 4, 4, 1, 8, 4, 4, 4|])
    )
  )
});

describe("Solver", () => {
  Expect.(
    test("toBe", () =>
      expect(
        solve(
          getInitialOptions(),
          Belt_Array.range(0, 63)
          ->Belt_Array.keep(x => !includes(centerCells, x)),
        ),
      )
      |> toEqual()
    )
  )
});
