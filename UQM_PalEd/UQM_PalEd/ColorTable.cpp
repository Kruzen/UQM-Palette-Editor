#include "ColorTable.h"

using namespace CTable;
using namespace System::Windows::Forms;

ColorTable::ColorTable(void)
{
    index = 0;
    numCluts = 0;
    table = gcnew array<Color>(MAX_CLUTS_PER_TABLE);
}

ColorTable::ColorTable(int index)
{
    this->index = index;
    numCluts = 0;
    table = gcnew array<Color>(MAX_CLUTS_PER_TABLE);
}

void CTable::ColorTable::setNumCluts(int num)
{
    numCluts = num;
}

void ColorTable::fillTable(BinaryReader^ br)
{
    int r, g, b = 0;

    if (numCluts == 0 || numCluts % BYTES_PER_COLOR != 0)
        return;
    
    br->BaseStream->Position += 2;// skip indexes of first and last clut

    for (int i = 0; br->BaseStream->Position < numCluts; i++)
    {
        r = br->ReadByte();
        g = br->ReadByte();
        b = br->ReadByte();
        /*MessageBox::Show("Color " + r, "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        MessageBox::Show("Color " + g, "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        MessageBox::Show("Color " + b, "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);*/
        table[i].FromArgb(0xFF, r, g, b);
    }
}

array<Color>^ ColorTable::returnTable(void)
{
    return table;
}

String^ ColorTable::debug(void)
{
    String^ s = "";
    for (int i = 0; i < 256; i++)
    {
        s += table[i].R.ToString();
        s += " ";
        s += table[i].G.ToString();
        s += " ";
        s += table[i].B.ToString();
        s += "\n";
    }
    MessageBox::Show("Color ", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return s;
}
