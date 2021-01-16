[@react.component]
let make = (~w=20, ~h=20) =>
  <div
    className={
      "bg-gray-200 border-red-400 border-2"
      ++ " w-"
      ++ string_of_int(w)
      ++ " h-"
      ++ string_of_int(h)
    }
  />;
