export interface ParsedLine
{
    timestamp: number;
    context: string;

    original: string;

    [key: string]: any;
}
