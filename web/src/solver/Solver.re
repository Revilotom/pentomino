open ShapeSelector;

open GridUtils;

open Constants;

type coords = array((int, int));

type moveOption = {
  shapeId,
  orientations: array(coords),
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
    let orientations =
      combined->Belt_Array.map(orientation =>
        orientation->Belt_Array.map(index => indexToCoords(index))
      );

    {orientations, shapeId: shape.id};
  });

let rec getAllPositions =
        (options: array(moveOption), freePlaces: array(int)) => {
  let blah =
    options->Belt_Array.map(opt =>
      {
        ...opt,
        orientations:
          opt.orientations
          ->Belt_Array.map(coordinates => {
              let transformed =
                freePlaces->Belt_Array.map(place =>
                  coordinates->Belt_Array.map(coord =>
                    addCoords(coord, indexToCoords(place))
                  )
                );

              let validMoves =
                transformed->Belt_Array.keep(coordindates =>
                  coordindates->Belt_Array.every(coord => {
                    let (x, y) = coord;
                    includes(freePlaces, coordsToindex(coord))
                    && x > (-1)
                    && x < 8
                    && y > (-1)
                    && y < 8;
                  })
                );

              // Js.log(removeDuplicates->Belt_Array.length);

              validMoves;
              // Js.log2(validMoves, opt.shapeId);
            })
          ->flatten
          ->Belt_Array.map(orientation =>
              orientation->Belt_Array.map(coord => coordsToindex(coord))
            )
          ->Belt.Set.fromArray(~id=(module BlahComp))
          ->Belt_Set.toArray
          ->Belt_Array.map(orientation =>
              orientation->Belt_Array.map(index => indexToCoords(index))
            ),
      }
    );
  blah;
};
