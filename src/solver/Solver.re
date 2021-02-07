open Logic;
open ShapeSelector;

open GridUtils;
open PairComparator;

let toArray = set =>
  set->Belt.Set.toArray->Belt_Array.map(elem => elem->Belt_Set.toArray);

module PairSetComparator =
  Belt.Id.MakeComparable({
    type t = Belt_Set.t(PairComparator.t, PairComparator.identity);

    let cmp = (a, b) => {
      let diff = Belt_Set.diff(a, b);

      let arrA = a->Belt_Set.toArray;

      let arrB = b->Belt_Set.toArray;
      let zipped = Belt_Array.zip(arrA, arrB);
      let compare =
        zipped->Belt_Array.map(((a1, b1)) => Pervasives.compare(a1, b1));

      diff->Belt_Set.size === 0 ? 0 : compare[0];
    };
  });

let toSet = array =>
  array
  ->Belt_Array.map(elem =>
      elem->Belt_Set.fromArray(~id=(module PairComparator))
    )
  ->Belt.Set.fromArray(~id=(module PairSetComparator));

let solve = () => {
  let initialOptions =
    init->Belt.Array.map(shape => {
      let rotations =
        Belt.Array.make(4, shape)
        ->Belt.Array.mapWithIndex((i, x) => {...x, orientation: i * 90});
      let combined =
        Belt.Array.concat(
          rotations,
          rotations->Belt.Array.map(x => {...x, flipped: true}),
        )
        ->Belt.Array.map(shape =>
            toCoords(Some(shape), shape.orientation, shape.flipped)
          );
      //   print_string(combined)
      Js.log(combined->Belt_Array.map(elem => elem->Belt_Set.toArray));
      combined->Belt.Set.fromArray(~id=(module PairSetComparator));
    });
  ();

  Js.log(initialOptions->Belt_Array.map(Belt_Set.size));
};
