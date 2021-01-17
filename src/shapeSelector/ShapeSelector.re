type shape = {
  id: int,
  orientation: int,
  component: React.element,
};

[@react.component]
let make = (~setSelected, ~selected, ~shapeArray: array(shape)) => {
  <>
    {shapeArray
     |> Array.map(x =>
          <div
            key={string_of_int(x.id)}
            className={
              "p-5 "
              ++ (selected === Some(x.id) ? "text-red-600" : "text-blue-500")
            }
            onClick={_ => setSelected(x.id)}>
            {x.component}
          </div>
        )
     |> React.array}
  </>;
};
