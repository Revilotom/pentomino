open Jest;
open Solver;
open PairComparator;

describe("Set", () => {
  //   Expect.(test("toBe", () =>
  //             expect(solve()) |> toBe()
  //           ));
  //   Expect.(
  //     test("no common", () => {
  //       let a = [|[|(1, 2), (1, 5)|], [|(8, 0), (9, 3)|]|];
  //       expect(a)
  //       |> toEqual(
  //            a
  //            ->Belt.Set.fromArray(~id=(module PairComparator))
  //            ->Belt_Set.toArray,
  //          );
  //     })
  //   );
  //   Expect.(
  //     test(" one tuple common ", () => {
  //       let a = [|[|(1, 2), (1, 5)|], [|(1, 2), (9, 3)|]|];
  //       expect(a)
  //       |> toEqual(
  //            a
  //            ->Belt.Set.fromArray(~id=(module PairComparator))
  //            ->Belt_Set.toArray,
  //          );
  //     })
  //   );
  //   Expect.(
  //     test("all tuple common ", () => {
  //       let a = [|[|(1, 2), (1, 5)|], [|(1, 2), (1, 5)|]|];
  //       expect([|[|(1, 2), (1, 5)|]|])
  //       |> toEqual(
  //            a
  //            ->Belt.Set.fromArray(~id=(module PairComparator))
  //            ->Belt_Set.toArray,
  //          );
  //   );
  Expect.
    //     })
    (
      test("I", () => {
        let a = [|
          [|((-2), 0), ((-1), 0), (0, 0), (1, 0), (2, 0)|],
          [|(0, 2), (0, 1), (0, 0), (0, (-1)), (0, (-2))|],
          [|(2, 0), (1, 0), (0, 0), ((-1), 0), ((-2), 0)|],
          [|(0, (-2)), (0, (-1)), (0, 0), (0, 1), (0, 2)|],
          [|(2, 0), (1, 0), (0, 0), ((-1), 0), ((-2), 0)|],
          [|(0, (-2)), (0, (-1)), (0, 0), (0, 1), (0, 2)|],
          [|((-2), 0), ((-1), 0), (0, 0), (1, 0), (2, 0)|],
          [|(0, 2), (0, 1), (0, 0), (0, (-1)), (0, (-2))|],
        |];

        let ans = [|
          [|((-2), 0), ((-1), 0), (0, 0), (1, 0), (2, 0)|],
          [|(2, 0), (1, 0), (0, 0), ((-1), 0), ((-2), 0)|],
        |];

        let toSet = array =>
          array
          ->Belt_Array.map(elem =>
              elem->Belt_Set.fromArray(~id=(module PairComparator))
            )
          ->Belt.Set.fromArray(~id=(module PairSetComparator));

        let toArray = set =>
          set
          ->Belt.Set.toArray
          ->Belt_Array.map(elem => elem->Belt_Set.toArray);

        expect(ans->toSet->Belt_Set.diff(a->toSet)->toArray) |> toEqual([||]);
      })
    )
});

describe("Solver", () => {
  Expect.(test("toBe", () =>
            expect(solve()) |> toBe()
          ))
});
