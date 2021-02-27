open Jest;
open Solver;
open GridUtils;

open ShapeSelector;

open Belt_Array;

describe("solver", () => {
  Expect.(
    test("make x", () => {
      expect(makeX()->Belt_MapInt.toArray)
      |> toEqual([|
           (1, [|"A", "B"|]),
           (2, [|"E", "F"|]),
           (3, [|"D", "E"|]),
           (4, [|"A", "B", "C"|]),
           (5, [|"C", "D"|]),
           (6, [|"D", "E"|]),
           (7, [|"A", "C", "E", "F"|]),
         |])
    })
  );

  Expect.(
    test("get smallest col x", () => {
      expect(x->getSmallestCol) |> toEqual(Some([|"A", "B"|]))
    })
  );

  Expect.(
    test("get smallest col x1", () => {
      let x1 =
        [|(4, [|"A", "B", "C"|]), (7, [|"A", "C", "E", "F"|])|]
        ->Belt_MapInt.fromArray;

      expect(x1->getSmallestCol) |> toEqual(Some([|"A", "B", "C"|]));
    })
  );

  Expect.(
    test("Select - newColumns", () => {
      let newColumns = select("A", y, x);
      expect(newColumns->Belt_MapInt.toArray)
      |> toEqual([|
           (2, [||]),
           (3, [|"D"|]),
           (5, [|"D"|]),
           (6, [|"D"|]),
         |]);
    })
  );

  Expect.(
    test("Solve ", () => {
      expect(solve(y, x, [||])) |> toEqual([|"B", "D", "F"|])
    })
  );
});
