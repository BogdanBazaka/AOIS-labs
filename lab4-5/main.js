import generateTruthTableVariables from "./generateTruthTableVariables.js";
import getVariableMap from "./getVariableMap.js";
import readFunc from "./readFunc.js";
import { getSDNF, getSKNF } from "./getSNF.js";
import getImplicants from "./Minimization/getImplicants.js";
import getConstituents from "./Minimization/getConstituents.js";
import calcMethod from "./Minimization/calcMethod.js";
import quineMethod from "./Minimization/quineMethod.js";
import karnoMethod from "./Minimization/karnoMethod.js";
import adder from "./adder.js";
import binaryCounter from "./binaryCounter.js";
import { outputsCountForBinaryCounter } from "./config.js";

(function start() {
  const func = "(A+((!B)*(!C)))";
  const variables = [...new Set(func.match(/[a-z]+/gi))];
  const sets = generateTruthTableVariables(variables.length);
  const varMap = getVariableMap(variables, sets);

  varMap.forEach((set, index) => sets[index].push(readFunc(func, set)));
  console.log("\n");

  const sdnf = getSDNF(varMap, sets);
  const sknf = getSKNF(varMap, sets);
  console.log("SDNF: ", sdnf);
  console.log("SKNF: ", sknf);
  console.log("\n");

  const implicantsSDNF = getImplicants(variables, sdnf.result);
  const implicantsSKNF = getImplicants(variables, sknf.result);
  console.log("Implicants:", "\n", implicantsSDNF, "\n", implicantsSKNF);
  console.log("\n");

  console.log("Calc Method:");
  console.log("SDNF: " + calcMethod(implicantsSDNF, "sdnf", varMap));
  console.log("SKNF: " + calcMethod(implicantsSKNF, "sknf", varMap));
  console.log("\n");

  const constituentsSDNF = getConstituents(sdnf.result);
  const constituentsSKNF = getConstituents(sknf.result);
  console.log("Quine Method:");
  console.log("SDNF: " + quineMethod(variables, constituentsSDNF, implicantsSDNF));
  console.log("SKNF: " + quineMethod(variables, constituentsSKNF, implicantsSKNF));
  console.log("\n");

  console.log("Karno Method:");
  console.log("SDNF: " + karnoMethod(func, "sdnf"));
  console.log("SKNF: " + karnoMethod(func, "sknf"));
  console.log("\n");

  console.log("Adder:");
  console.log(adder(varMap, 'sdnf'));
  console.log("\n");

  console.log("Binary Counter:");
  binaryCounter(outputsCountForBinaryCounter);
  console.log("\n");
})();