[@react.component]
let make = (~setSelected, ~selected) => {
  <>
    {[|<F />, <I />, <L />, <N />, <P />, <V />, <W />, <X />, <Y />|]
     |> Array.mapi((i, x) =>
          <div
            key={string_of_int(i)}
            className={
              "p-5 "
              ++ (selected === Some(i) ? "text-red-600" : "text-blue-500")
            }
            onClick={_ => setSelected(i)}>
            x
          </div>
        )
     |> React.array}
  </>;
};
