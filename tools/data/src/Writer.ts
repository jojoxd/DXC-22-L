import {ParsedLine} from "./ParsedLine";

export interface Writer
{
    cacheOriginal(line: string);

    write(line: ParsedLine);
    close();
}
