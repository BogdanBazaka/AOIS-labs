import getConstituents from "./getConstituents.js";

export default function getImplicants(variables, snf) {
  let implicants = [];
  let constituents = getConstituents(snf);

  while (true) {
    let flag = false;
    const used = [];

    constituents.forEach((constituent, index) => {
      constituent.split("").forEach((item, varIndex, arr) => {
        if (variables.includes(item)) {
          let variable = item;
          if (arr[varIndex - 1] === "!") variable = "!" + variable;
          constituents.forEach((constituent_2, index_2) => {
            if (index_2 !== index && !constituent_2.includes(variable)) {
              let str_1, str_2;
              let pair = [constituent, constituent_2];
              if (variable.includes("!") && constituent_2.includes(variable)) {
                pair.reverse();
              }
              str_1 =
                pair[0].substring(0, constituent.indexOf(variable)) +
                pair[0].substring(constituent.indexOf(variable) + 2);
              str_2 =
                pair[1].substring(0, constituent_2.indexOf(variable[1])) +
                pair[1].substring(constituent_2.indexOf(variable[1]) + 1);
              if (str_1 === str_2) {
                if (str_1.includes("++") || str_1.includes("**")) {
                  let prev;
                  for (let l of str_1) {
                    if (l === prev) {
                      str_1 =
                        str_1.substring(0, str_1.indexOf(prev + l)) +
                        str_1.substring(str_1.indexOf(prev + l) + 1);
                      break;
                    }
                    prev = l;
                  }
                } else if (str_1[0] === "+" || str_1[0] === "*") {
                  str_1 = str_1.substring(1);
                } else if (str_1[str_1.length - 1] === "+" || str_1[str_1.length - 1] === "*") {
                  str_1 = str_1.slice(0, -1);
                }
                implicants.push(str_1);
                flag = true;
                used.push(constituent, constituent_2);
              }
            }
          });
        }
      });
    });
    if (flag) {
      constituents.forEach(constituent => {
        if(!used.includes(constituent)) implicants.push(constituent);
      });
      constituents = [...Array.from(new Set(implicants))];
      implicants = [];
    }
    else return constituents;
  }
}