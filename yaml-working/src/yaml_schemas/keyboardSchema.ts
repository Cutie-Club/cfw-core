import { z } from "zod";

const infoBlock = z.object({
  keyboard: z.string(),
  maintainer: z.string(),
  description: z.string(),
});

const hardwareBlock = z.object({
  processor: z.string(),
  matrix: z.object({
    rows: z.array(z.string().regex(/[A-Z]\d+/, "Invalid pin name specified")).nonempty(),
    cols: z.array(z.string().regex(/[A-Z]\d+/, "Invalid pin name specified")).nonempty(),
  }).strict(),
  indicators: z.optional(z.object({})),
  usb: z.object({
    productID: z.number(),
    vendorID: z.number(),
    serialNo: z.optional(z.string()),
    versionNo: z.number(),
    manufacturer: z.string(),
    product: z.string(),
  }),
});

function generateLayoutBlock(layoutsList: string[]) {
  const layoutBlockObject: Record<string, any> = {};

  layoutsList.forEach((layoutName) => {
    layoutBlockObject[layoutName] = z.optional(
      z.array(z.array(z.string().nonempty()))
    );
  });

  return z
    .object(layoutBlockObject)
    .strict()
    .refine(
      (objectToTest) => Object.keys(objectToTest).length !== 0,
      "At least 1 layout must be supported!"
    );
}

const keyboardSchema = z.object({
  info: infoBlock,
  hardware: hardwareBlock,
  layouts: generateLayoutBlock([
    "4x4_Grid",
    "2x4_Grid",
    "4x4_Grid_Missing_Center",
  ]),
});

export default keyboardSchema;
