import { allowedOperations } from "./config.js";

export default function readFunc(func, set) {
  const operationStack = [];
  const variablesStack = [];

  for (let l of func) {
    if (l !== " ") {
      if (allowedOperations.includes(l)) {
        if (l === ")") {
          if (operationStack.at(-1) === "(") {
            operationStack.pop();
            if (operationStack.length !== 0) {
              if (operationStack.at(-1) === "!") {
                variablesStack.push(calc(operationStack.pop(), variablesStack.pop()));
              } else if (operationStack.at(-1) !== "(") {
                variablesStack.splice(-2, 2, calc(
                    operationStack.pop(),
                    variablesStack.at(-1),
                    variablesStack.at(-2)
                  )
                );
              }
            }
          } else if (operationStack.at(-1) !== "(" && ")") {
            if (operationStack.at(-1) === "!") {
              variablesStack.push(
                calc(operationStack.pop(), variablesStack.pop())
              );
            } else if (operationStack.length !== 0) {
              variablesStack.splice(-2, 2, calc(
                  operationStack.pop(),
                  variablesStack.at(-1),
                  variablesStack.at(-2)
                )
              );
            }
            operationStack.pop();
          }
        } else operationStack.push(l);
      } else {
        if (set.has(l)) variablesStack.push(set.get(l));
        else return console.log("undefined variable");
        if (
          operationStack.length !== 0 &&
          operationStack.at(-1) !== "(" &&
          ")"
        ) {
          if (operationStack.at(-1) === "!") {
            variablesStack.push(calc(operationStack.pop(), variablesStack.pop()));
          } else {
            variablesStack.splice(-2, 2, calc(
                operationStack.pop(),
                variablesStack.at(-1),
                variablesStack.at(-2)
              )
            );
          }
        }
      }
    }
  }
  if (operationStack.length != 0) {
    variablesStack.push(calc(operationStack.pop(), variablesStack.at(-1), variablesStack.at(-2)));
  }
  return variablesStack.pop();
}

function calc(sign, a, b) {
  if (typeof a === "string" || typeof b === "string") {
    let operand_1 = a;
    let operand_2 = b;
    if (typeof a === "string" && typeof b === "string") {
      if (a === b) return a;
      else {
        if (operand_2.includes("!")) {
          [operand_1, operand_2] = [operand_2, operand_1];
        }
        if (sign === "*") return 0;
        else if (sign === "+") return 1;
      }
    } else {
      if (typeof a !== "number" && typeof a !== "boolean" && b !== undefined) {
        [operand_1, operand_2] = [operand_2, operand_1];
      }
      if (sign === "*") {
        if (operand_1) return operand_2;
        return 0;
      } else if (sign === "+") {
        if (operand_1) return 1;
        return operand_2;
      } else if (sign === "!") {
        return "!" + operand_1;
      }
    }
  } else {
    if (sign === "*") {
      if (a && b) return 1;
      return 0;
    } else if (sign === "+") {
      if (!a && !b) return 0;
      return 1;
    } else if (sign === "!") {
      return !a;
    } else if (sign === ">") {
      if (a && !b) return 0;
      return 1;
    } else if (sign === "=") {
      if (a == b) return 1;
      return 0;
    }
  }
}