[@react.component]
let make = () => {
  <div className="flex justify-items-auto justify-center">
    <div
      className="justify-center h-full flex flex-wrap content-start  "
      style={ReactDOM.Style.make(~width="700px", ())}>
      {Array.make(64, None)
       |> Array.mapi((i, _) => <Cell key={string_of_int(i)} />)
       |> React.array}
    </div>
  </div>;
};
