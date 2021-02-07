open Logic;
open ShapeSelector;

open GridUtils;
open PairComparator;

let toArray = set => set->Belt.Set.toArray;
module BlahComp =
  Belt.Id.MakeComparable({
    type t = array(int);

    let cmp = (arrA, arrB) => {
      arrA |> Array.sort((a, b) => a - b);
      arrB |> Array.sort((a, b) => a - b);

      let zipped = Belt_Array.zip(arrA, arrB);
      let c =
        zipped->Belt_Array.map(((a1, b1)) => Pervasives.compare(a1, b1));

      c->Belt_Array.reduce(0, (acc, curr) => acc === 0 ? curr : acc);
      // diff->Belt_Set.size === 0 ? 0 : c[0];
    };
  });

let toSet = array =>
  array
  ->Belt_Array.map(x => x->Belt_Array.map(coordsToindex))
  ->Belt.Set.fromArray(~id=(module BlahComp));

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
            ->Belt_Set.toArray
            ->Belt_Array.map(coordsToindex)
          );
      //   print_string(combined)
      // Js.log(combined);
      combined->Belt.Set.fromArray(~id=(module BlahComp));
    });
  ();

  Js.log(initialOptions->Belt_Array.map(Belt_Set.size));
};
