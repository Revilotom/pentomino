open ShapeSelector;

open GridUtils;

open Constants;

type columns = Belt_MapInt.t(array(Belt_MapString.key));

type rows = Belt_MapString.t(array(int));

module IntCmp =
  Belt.Id.MakeComparable({
    type t = int;
    let cmp = Pervasives.compare;
  });

module StrCmp =
  Belt.Id.MakeComparable({
    type t = string;
    let cmp = Pervasives.compare;
  });

let makeColumns = (rows: rows) => {
  let keys = rows->Belt_MapString.keysToArray;
  let values =
    rows
    ->Belt_MapString.valuesToArray
    ->flatten
    ->Belt_Set.fromArray(~id=(module IntCmp))
    ->Belt_Set.toArray;
  values
  ->Belt_Array.map(v =>
      (
        v,
        keys->Belt_Array.keep(k =>
          rows
          ->Belt_MapString.get(k)
          ->Belt_Option.getWithDefault([||])
          ->includes(v)
        ),
      )
    )
  ->Belt_MapInt.fromArray;
};

let getSmallestCol = (columns: columns) =>
  columns
  ->Belt_MapInt.map(Belt_Array.length)
  ->Belt_MapInt.reduce(None, (acc, curK, curV) =>
      acc->Belt_Option.isNone
        ? Some((curK, curV))
        : acc->Belt_Option.map(v => {
            let (_, accV) = v;
            curV < accV ? (curK, curV) : v;
          })
    )
  ->Belt_Option.flatMap(((k, _)) => columns->Belt_MapInt.get(k));

let select = (rts: string, rows: rows, columns: columns) => {
  let cols = rows->Belt_MapString.get(rts)->Belt_Option.getWithDefault([||]);

  let selected =
    cols
    ->Belt_Array.map(c =>
        columns->Belt_MapInt.get(c)->Belt_Option.getWithDefault([||])
      )
    ->flatten;

  columns
  ->Belt_MapInt.removeMany(cols)
  ->Belt_MapInt.map(row => row->Belt_Array.keep(c => !selected->includes(c)));
};

let rec solveHelper =
        (rows: rows, columns: columns, solution: array(string))
        : array(array(string)) =>
  // Js.log(columns->Belt_MapInt.toArray);
  if (columns->Belt_MapInt.size === 0) {
    Js.log("solution");
    Js.log(solution);

    // raise(Not_found);

    [|solution|];
  } else {
    getSmallestCol(columns)
    ->Belt_Option.getWithDefault([||])
    ->Belt_Array.map(r =>
        solveHelper(
          rows,
          select(r, rows, columns),
          solution->Belt_Array.concat([|r|]),
        )
      )
    ->flatten;
  };

let solve = (rows: rows, columns: columns) =>
  solveHelper(rows, columns, [||]);
