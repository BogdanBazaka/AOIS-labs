import readFunc from "../readFunc.js";
import { variablesCountForKarnoMethod } from "../config.js";

function getKarnoMap(sets, func) {
  const results = [];
  sets[1].forEach((posB, indexB) => {
    let column = [];
    sets[0].forEach((posA) => {
      column.push(readFunc(func, new Map([["A", posA], ["B", posB], ["C", sets[2][indexB]]])));
    });
    results.push(column);
  });
  return results;
}

function getKarnoGroups(results, typeValue) {
  let groups = [];
  
  for (let i = 0; i < results.length; i++) {
    if (results[i].every((elem) => elem == typeValue)) {
      groups.push({ type: "col", index: i });
      if (
        results[i + 1] !== undefined &&
        results[i + 1].toString() === results[i].toString()
      ) {
        groups.splice(-1, 1, { type: "rect", index: [i, i + 1] });
        i++;
      } else if (
        results[i + 1] === undefined &&
        results[0].toString() === results.at(-1).toString()
      ) {
        groups.pop();
        if (groups.find((item) => item.type === "col" && item.index === 0)) {
          groups.splice(0, 1, {
            type: "rect",
            index: [0, results.length - 1],
          });
        } else groups.push({ type: "rect", index: [0, results.length - 1] });
      }
    }
  }
  for (let r = 0; r < 2; r++) {
    let flag = false;
    if (results.length === variablesCountForKarnoMethod) {
      if ([results[0][r], results[1][r], results[2][r], results[3][r]].every(res => res == typeValue)) {
        groups.push({ type: "row", colIndexes: [0, 1, 2, 3], rowIndex: r });
        flag = true;
      }
      if (!flag){
        for (let i = 0; i < results.length; i++) {
          if (results[i + 1] !== undefined) {
            if (results[i][r] == typeValue && results[i + 1][r] == typeValue) {
              groups.push({ type: "row", colIndexes: [i, i + 1], rowIndex: r });
            }
          } else if ([results[i][r], results[0][r]].every(res => res == typeValue)) {
            groups.push({ type: "row", colIndexes: [0, i], rowIndex: r });
          }
        }
      }
    } else return console.log("incorrect number of variables")
  }
  return groups;
}

function formateKarnoGroups(groupss) {
  let groups = groupss;
  groups.forEach((group1, index1) => {
    if (group1.type === 'row') {
      if (group1.colIndexes.length === 2) {
        groups.forEach((group_2, index2) => {
          if (index1 !== index2 && group_2.type === 'row'
          && group_2.colIndexes.toString() === group1.colIndexes.toString()) {
            groups[index1] = groups[index2] = 0;
          }
        });
      }
    }
  });
  groups = groups.filter(group => group !== 0);

  let col;
  groups.forEach((group_1, index_1) => {
    if (group_1.type === "row") {
      groups.forEach((group_2, index_2) => {
        if (index_1 !== index_2 && group_2.type === "row") {
          group_1.colIndexes.forEach(colIndex => {
            if (group_2.colIndexes.includes(colIndex)) {
              col = colIndex;
            }
          });
        }
      });
    }
  });
  groups.forEach((group, index) => {
    if (group.type === "col" && group.index === col) {
      return groups.splice(index, 1);
    }
  });
  return groups;
}

function getKarnoMNF(groups, sets, typeValue) {
  const mnf = [];
  groups.forEach((group) => {
    let implicant = [];
    if (group.type === "col") {
      if (sets[1][group.index] !== typeValue) implicant.push("!B");
      else implicant.push("B");
      if (sets[2][group.index] !== typeValue) implicant.push("!C");
      else implicant.push("C");
    } else if (group.type === "rect") {
      if (sets[0][group.index[0]] === sets[0][group.index[1]]) {
        if (sets[0][group.index[0]] !== typeValue) implicant.push("!A");
        else implicant.push("A");
      } else {
        if (sets[2][group.index[0]] !== typeValue) implicant.push("!C");
        else implicant.push("C");
      }
    } else if (group.type === "row") {
      if (group.colIndexes.length === 2) {
        if (sets[1][group.colIndexes[0]] === sets[1][group.colIndexes[1]]) {
          if (sets[1][group.colIndexes[0]] !== typeValue) implicant.push("!B");
          else implicant.push("B");
        } else {
          if (sets[2][group.colIndexes[0]] !== typeValue) implicant.push("!C");
          else implicant.push("C");
        }
      }
      if (sets[0][group.rowIndex] !== typeValue) implicant.push("!A");
      else implicant.push("A");
      implicant.reverse();
    }
    mnf.push(implicant);
  });
  return mnf;
}

export default function karnoMethod(func, funcType) {
  let typeValue = 1;
  if (funcType === "sknf") typeValue = 0;

  const sets = [
    [0, 1],
    [0, 0, 1, 1],
    [0, 1, 1, 0],
  ];

  const results = getKarnoMap(sets, func);
  const groups = formateKarnoGroups(getKarnoGroups(results, typeValue));
  const mnf = getKarnoMNF(groups, sets, typeValue);

  let outSign = "+";
  let inSign = "*";
  if (funcType === "sknf") [outSign, inSign] = [inSign, outSign];
  return (
    "(" + mnf.map((set) => set.join(`${inSign}`)).join(`)${outSign}(`) + ")"
  );
}