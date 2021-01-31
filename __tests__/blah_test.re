open Jest;
open Solver;

describe("Expect", () => {
  Expect.(test("toBe", () =>
            expect(solve()) |> toBe()
          ))
});
