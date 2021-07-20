import { readFile } from "fs/promises";
import { parse } from "yaml";

export function parseFile(filePath: string): Promise<any> {
  return readFile(filePath).then((fileContents) =>
    parse(fileContents.toString())
  );
}
