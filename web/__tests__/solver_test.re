open Jest;
open Solver;
open GridUtils;

open ShapeSelector;
open MoveGenerator;

open Belt_Array;

describe("solver", () => {
  let y =
    Belt_MapString.fromArray([|
      ("A", [|"1", "4", "7"|]),
      ("B", [|"1", "4"|]),
      ("C", [|"4", "5", "7"|]),
      ("D", [|"3", "5", "6"|]),
      ("E", [|"2", "3", "6", "7"|]),
      ("F", [|"2", "7"|]),
    |])
    ->Belt_MapString.map(Belt_SetString.fromArray);

  let x = makeColumns(y);

  Expect.(
    test("make x", () => {
      expect(
        x->Belt_MapString.map(Belt_SetString.toArray)->Belt_MapString.toArray,
      )
      |> toEqual([|
           ("1", [|"A", "B"|]),
           ("2", [|"E", "F"|]),
           ("3", [|"D", "E"|]),
           ("4", [|"A", "B", "C"|]),
           ("5", [|"C", "D"|]),
           ("6", [|"D", "E"|]),
           ("7", [|"A", "C", "E", "F"|]),
         |])
    })
  );

  Expect.(
    test("get smallest col x", () => {
      expect(x->getSmallestCol->Belt_Option.map(Belt_SetString.toArray))
      |> toEqual(Some([|"A", "B"|]))
    })
  );

  Expect.(
    test("get smallest col x1", () => {
      let x1 =
        [|("4", [|"A", "B", "C"|]), ("7", [|"A", "C", "E", "F"|])|]
        ->Belt_MapString.fromArray
        ->Belt_MapString.map(Belt_SetString.fromArray);

      expect(x1->getSmallestCol->Belt_Option.map(Belt_SetString.toArray))
      |> toEqual(Some([|"A", "B", "C"|]));
    })
  );

  Expect.(
    test("Select - newColumns", () => {
      let newColumns = select("A", y, x);
      expect(
        newColumns
        ->Belt_MapString.map(Belt_SetString.toArray)
        ->Belt_MapString.toArray,
      )
      |> toEqual([|
           ("2", [||]),
           ("3", [|"D"|]),
           ("5", [|"D"|]),
           ("6", [|"D"|]),
         |]);
    })
  );
  Expect.(
    test("Solve ", () => {
      expect(solve(y, x)) |> toEqual([|[|"B", "D", "F"|]|])
    })
  );
  Expect.(
    test("Solve matrix with 3 solutions", () => {
      let rows =
        Belt_MapString.fromArray([|
          ("A", [|"1"|]),
          ("B", [|"2", "3"|]),
          ("C", [|"1", "4"|]),
          ("D", [|"3", "4"|]),
          ("E", [|"2"|]),
          ("F", [|"3"|]),
        |])
        ->Belt_MapString.map(Belt_SetString.fromArray);
      expect(solve(rows, makeColumns(rows)))
      |> toEqual([|[|"A", "D", "E"|], [|"C", "B"|], [|"C", "E", "F"|]|]);
    })
  );
  Expect.(
    test("Solve Pentomino ", () => {
      let rows =
        allPositions
        ->mapWithIndex((i, shape) => {
            shape.positions
            ->map(pos =>
                (
                  shapeToString(shape.shape.id)
                  ++ "-"
                  ++ pos
                     ->map(coordsToindex)
                     ->map(string_of_int)
                     ->joinWith("-", a => a),
                  pos
                  ->map(coordsToindex)
                  ->map(string_of_int)
                  ->concat([|shapeToString(shape.shape.id)|]),
                )
              )
          })
        ->flatten
        ->Belt_MapString.fromArray
        ->Belt_MapString.map(Belt_SetString.fromArray);
      let columns = makeColumns(rows);
      expect(solve(rows, columns)->length) |> toEqual(520); //65 if reflections are removed
    })
  );
});
