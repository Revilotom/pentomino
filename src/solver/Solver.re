open Logic;
open ShapeSelector;

open GridUtils;
open PairComparator;

type option = {
  shapeId,
  cells: array(array(int)),
};

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
    };
  });

let getInitialOptions = () =>
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
        )
      ->Belt.Set.fromArray(~id=(module BlahComp))
      ->Belt_Set.toArray;
    {cells: combined, shapeId: shape.id};
  });

let solve = (options: array(option), freePlaces: array(int)) => {
  let blah =
    options->Belt_Array.map(opt =>
      opt.cells
      ->Belt_Array.map(indexes => {
          let transformed =
            freePlaces->Belt_Array.map(place =>
              indexes->Belt_Array.map(coord =>
                addCoords(indexToCoords(coord), indexToCoords(place))
                ->coordsToindex
              )
            );
          let validMoves =
            transformed->Belt_Array.keep(xs =>
              xs->Belt_Array.every(x => includes(freePlaces, x))
            );

          Js.log2(validMoves, opt.shapeId);
        })
    );
  ();
};
