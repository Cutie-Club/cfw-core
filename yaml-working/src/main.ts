import { parseFile } from "./parseYaml";
import { keyboardSchema } from "./yaml_schemas";
import { z } from "zod";
import chalk from "chalk";
import { collectionFromPath } from "yaml/dist/nodes/Collection";
import { type } from "os";

const successMessage = (message: string) => {
  console.log(chalk.green("[OK]") + " " + message);
};

const warningMessage = (message: string) => {
  console.log(chalk.keyword("orange")("[WARN]") + " " + message);
};

const errorMessage = (message: string) => {
  console.error(chalk.red("(ಥ﹏ಥ) ") + message);
};

const errorList = (message: string, list: string[]) => {
  errorMessage(message);
  console.group();
  console.error(list.map((listItem) => `"${listItem}"`).join(", "));
  console.groupEnd();
  console.log();
};

const validateKeyboardSchema = keyboardSchema.parse;

const obj: Record<string, number> = {
  "hehe":1
}

type ZodIssueHandler = {
  "invalid_type": (path: string, issue: z.ZodInvalidTypeIssue) => void,
  "unrecognized_keys": (path: string, issue: z.ZodUnrecognizedKeysIssue) => void,
  "invalid_union": (path: string, issue: z.ZodInvalidUnionIssue) => void,
  "invalid_enum_value": (path: string, issue: z.ZodInvalidEnumValueIssue) => void,
  "invalid_arguments": (path: string, issue: z.ZodInvalidArgumentsIssue) => void,
  "invalid_return_type": (path: string, issue: z.ZodInvalidReturnTypeIssue) => void,
  "invalid_date": (path: string, issue: z.ZodInvalidDateIssue) => void,
  "invalid_string": (path: string, issue: z.ZodInvalidStringIssue) => void,
  "too_small": (path: string, issue: z.ZodTooSmallIssue) => void,
  "too_big": (path: string, issue: z.ZodTooBigIssue) => void,
  "invalid_intersection_types": (path: string, issue: z.ZodInvalidIntersectionTypesIssue) => void,
};

const keyboardSchemaErrorHandler: ZodIssueHandler = {
  "unrecognized_keys": (path: string, issue: z.ZodUnrecognizedKeysIssue): void => {
    errorList(
      `In ${chalk.italic(path)}, the following property is invalid:`,
      issue.keys
    );
  },
  "invalid_type": (path: string , issue: z.ZodInvalidTypeIssue): void => {
    if (issue.received === "undefined" || issue.received === "null") {
      errorList("The following required property was not provided:", [
        path
      ]);
    }
  }
}

parseFile("./keyboard.yaml")
  // .then(console.log)
  .then(validateKeyboardSchema)
  .catch((error: z.ZodError) =>
    error.issues.forEach((issue) => {
      const issuePath = issue.path.join(".");
      keyboardSchemaErrorHandler[issue.code](issuePath, issue);
    })
  );
