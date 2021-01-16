[@react.component]
let make = (~setSelected) => {
  <div className="">
    {[|<F />, <I />, <L />, <N />, <P />, <V />, <W />, <X />, <Y />|]
     |> Array.mapi((i, x) =>
          <div className="p-5" onClick={_ => setSelected(_ => Some(i))}>
            x
          </div>
        )
     |> React.array}
  </div>;
};
