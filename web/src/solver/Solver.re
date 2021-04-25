open ShapeSelector;

open GridUtils;

open Constants;

type map = Belt_MapString.t(Belt_SetString.t);

let emptySet = [||]->Belt_SetString.fromArray;

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

let makeColumns = (rows: map) => {
  let keys = rows->Belt_MapString.keysToArray;
  let values =
    rows
    ->Belt_MapString.valuesToArray
    ->Belt_Array.map(Belt_SetString.toArray)
    ->flatten
    ->Belt_SetString.fromArray
    ->Belt_SetString.toArray;
  values
  ->Belt_Array.map(v =>
      (
        v,
        keys
        ->Belt_Array.keep(k =>
            rows
            ->Belt_MapString.get(k)
            ->Belt_Option.getWithDefault(emptySet)
            ->Belt_SetString.has(v)
          )
        ->Belt_SetString.fromArray,
      )
    )
  ->Belt_MapString.fromArray;
};

let getSmallestCol = (columns: map) =>
  columns
  ->Belt_MapString.map(Belt_SetString.size)
  ->Belt_MapString.reduce(None, (acc, curK, curV) =>
      acc->Belt_Option.isNone
        ? Some((curK, curV))
        : acc->Belt_Option.map(v => {
            let (_, accV) = v;
            curV < accV ? (curK, curV) : v;
          })
    )
  ->Belt_Option.flatMap(((k, _)) => columns->Belt_MapString.get(k));

let select = (rts: string, rows: map, columns: map) => {
  let cols =
    rows->Belt_MapString.get(rts)->Belt_Option.getWithDefault(emptySet);

  let selected =
    cols
    ->Belt_SetString.toArray
    ->Belt_Array.map(c =>
        columns
        ->Belt_MapString.get(c)
        ->Belt_Option.getWithDefault(emptySet)
        ->Belt_SetString.toArray
      )
    ->flatten;

  columns
  ->Belt_MapString.removeMany(cols->Belt_SetString.toArray)
  ->Belt_MapString.map(row => row->Belt_SetString.removeMany(selected));
};

let prettifySolution = (res: array(string)) => {
  let map =
    res
    ->Belt_Array.map(str => {
        let splitted = str |> String.split_on_char('-');
        let (letter, cells) =
          switch (splitted) {
          | [] => ("A", [])
          | [letter, ...cells] => (letter, cells)
          };
        let list =
          cells->Belt_List.map(cell => (cell->int_of_string, letter));
        list->Belt_List.toArray;
      })
    ->flatten
    ->Belt_MapInt.fromArray;

  let chars =
    Belt_Array.make(64, "")
    ->Belt_Array.mapWithIndex((i, _) =>
        map->Belt_MapInt.getWithDefault(i, "*")
      );

  [|
    Belt_Array.slice(chars, ~offset=0, ~len=8),
    Belt_Array.slice(chars, ~offset=8, ~len=8),
    Belt_Array.slice(chars, ~offset=16, ~len=8),
    Belt_Array.slice(chars, ~offset=24, ~len=8),
    Belt_Array.slice(chars, ~offset=32, ~len=8),
    Belt_Array.slice(chars, ~offset=40, ~len=8),
    Belt_Array.slice(chars, ~offset=48, ~len=8),
    Belt_Array.slice(chars, ~offset=56, ~len=8),
    Belt_Array.slice(chars, ~offset=64, ~len=8),
  |]
  ->Belt_Array.map(arr => arr->Belt_Array.joinWith("", x => x))
  ->Belt_Array.joinWith("\n", x => x);
};

let rec solveHelper =
        (rows: map, columns: map, solution: array(string))
        : array(array(string)) =>
  // Js.log(columns->Belt_MapInt.toArray);
  if (columns->Belt_MapString.size === 0) {
    Js.log("solution");
    Js.log(solution);
    Js.log(prettifySolution(solution));

    // raise(Not_found);

    [|solution|];
  } else {
    getSmallestCol(columns)
    ->Belt_Option.getWithDefault(emptySet)
    ->Belt_SetString.toArray
    ->Belt_Array.map(r =>
        solveHelper(
          rows,
          select(r, rows, columns),
          solution->Belt_Array.concat([|r|]),
        )
      )
    ->flatten;
  };

let solve = (rows: map, columns: map) => solveHelper(rows, columns, [||]);
