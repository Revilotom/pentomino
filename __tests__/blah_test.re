open Jest;
open Solver;

describe("Expect", () => {
  Expect.(test("toBe", () =>
            expect(solve()) |> toBe()
          ));
  Expect.(
    test("set, no common", () => {
      let a = [|[|(1, 2), (1, 5)|], [|(8, 0), (9, 3)|]|];
      expect(a)
      |> toEqual(
           a
           ->Belt.Set.fromArray(~id=(module PairComparator))
           ->Belt_Set.toArray,
         );
    })
  );

  Expect.(
    test("set, one tuple common ", () => {
      let a = [|[|(1, 2), (1, 5)|], [|(1, 2), (9, 3)|]|];
      expect(a)
      |> toEqual(
           a
           ->Belt.Set.fromArray(~id=(module PairComparator))
           ->Belt_Set.toArray,
         );
    })
  );

  Expect.(
    test("set, all tuple common ", () => {
      let a = [|[|(1, 2), (1, 5)|], [|(1, 2), (1, 5)|]|];

      expect([|[|(1, 2), (1, 5)|]|])
      |> toEqual(
           a
           ->Belt.Set.fromArray(~id=(module PairComparator))
           ->Belt_Set.toArray,
         );
    })
  );
});
