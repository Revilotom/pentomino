open ShapeSelector;

let init: array(shape) =
  [|
    (<F />, Pink, F),
    // (<I />, Red, I),
    // (<L />, Blue, L),
    // (<N />, Green, N),
    // (<P />, Orange, P),
    // (<V />, Indigo, V),
    // (<W />, Purple, W),
    // (<X />, Yellow, X),
    // (<Y />, Teal, Y),
    // (<Z />, Yellow, Z),
    // (<U />, Indigo, U),
    // (<T />, Blue, T),
  |]
  |> Array.map(((component, color, id)) =>
       {component, id, orientation: 0, flipped: false, cell: None, color}
     );
