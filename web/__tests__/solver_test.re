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
  )
});
