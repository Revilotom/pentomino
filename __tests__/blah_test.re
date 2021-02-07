open Jest;
open Solver;
open PairComparator;

describe("Solver", () => {
  Expect.(
    test("toBe", () =>
      expect(getInitialOptions()->Belt_Array.map(Belt_Set.size))
      |> toEqual([|8, 2, 8, 8, 8, 4, 4, 1, 8, 4, 4, 4|])
    )
  )
});
