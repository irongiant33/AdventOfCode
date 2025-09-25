#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <sstream>

#define DEBUG false
#define MASK 0xFFFF

using namespace std;

class Command
{
public:
    string rhs;
    string output_wire;
    string lhs;
    string func_str;

    Command(void)
    {
        this->rhs = "";
        this->lhs = "";
        this->output_wire = "";
        this->func_str = "";
    }

    int operate(void)
    {
        int ret_val = -1;
        if(this->func_str == "NOT")
        {
            ret_val = MASK ^ stoi(this->rhs);        
        }
        else if(this->func_str == "OR")
        {
            ret_val = stoi(this->lhs) | stoi(this->rhs);
        }
        else if(this->func_str == "AND")
        {
            ret_val = stoi(this->lhs) & stoi(this->rhs);
        }
        else if(this->func_str == "LSHIFT")
        {
            ret_val = MASK & (stoi(this->lhs) << stoi(this->rhs));
        }
        else if(this->func_str == "RSHIFT")
        {
            ret_val = stoi(this->lhs) >> stoi(this->rhs);
        }
        else if(this->func_str == "IS")
        {
            ret_val = stoi(this->rhs);
        }
        else
        {
            cout << "Unknown function string " << this->func_str << endl;
            exit(1);
        }
        return ret_val;
    }

    void command_initialization(string rhs, string output_wire, string func_str = "NOT", string lhs="")
    {
        this->rhs = rhs;
        this->output_wire = output_wire;
        this->lhs = lhs;
        this->func_str = func_str;
    }
};


ostream & operator<<(ostream & out, Command & my_command)
{
    out << my_command.lhs << " " <<  my_command.func_str << " " << my_command.rhs << " -> " << my_command.output_wire;
    return out;
}

string solve_mappings(map <string, string> * wire_dict, list <class Command> * commands)
{
    while(wire_dict->end() == wire_dict->find("a") && commands->size() > 0)
    {
        Command current_command = commands->front();
        commands->pop_front();
        // check to see if lhs and rhs are in wire_dict
        if(current_command.lhs.size() > 0 && wire_dict->end() != wire_dict->find(current_command.lhs))
        {
            current_command.lhs = wire_dict->at(current_command.lhs);
        }
        if(wire_dict->end() != wire_dict->find(current_command.rhs))
        {
            current_command.rhs = wire_dict->at(current_command.rhs);
        }
        // check current command for completion
        try
        {
            int tmp; // just to check if stoi conversion works
            if(current_command.lhs.size() != 0)
            {
                tmp = stoi(current_command.lhs);
            }
            tmp = stoi(current_command.rhs);
            // if we got to this point, both conversions were successful.
            int result = current_command.operate();
            (*wire_dict)[current_command.output_wire] = to_string(result);
        }
        catch(invalid_argument const & ex)
        {
            // getting here means either the lhs or rhs do not have a value yet
            commands->push_back(current_command);
        }
    }
    if(DEBUG)
    {
        cout << "Wire dict size: " << wire_dict->size() << endl;
        cout << "Commands size: " << commands->size() << endl;
    }
    return wire_dict->at("a");
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cout << "Usage: ./day7 input.txt\n";
        exit(1);
    }
    ifstream file(argv[1]);
    map <string, string> wire_map_pt1;
    map <string, string> wire_map_pt2;
    list < class Command > commands_pt1;
    list < class Command > commands_pt2;
    string line;
    getline(file, line);
    while(line.size() > 0)
    {
        list < string > line_items;
        istringstream line_stream(line);
        string item;
        bool added_command = true;
        Command my_command;
        while(line_stream >> item)
        {
            line_items.push_back(item);
        }
        if(line_items.size() == 3) //assignment
        {
            string first_item = line_items.front();
            line_items.pop_front();
            string output = line_items.back();
            line_items.pop_back();
            try
            {
                //assignment is a number to wire
                int tmp = stoi(first_item);
                wire_map_pt1[output] = first_item;
                wire_map_pt2[output] = first_item;
                added_command = false;
            }
            catch(invalid_argument const & ex)
            {
                // assignment is a wire to another wire
                my_command.command_initialization(first_item, output, "IS");
                commands_pt1.push_back(my_command);
                commands_pt2.push_back(my_command);
            }
        }
        else if(line_items.size() == 4) //unary operation
        {
            string operation = line_items.front();
            line_items.pop_front();
            string first_item = line_items.front();
            line_items.pop_front();
            string output = line_items.back();
            line_items.pop_back();
            my_command.command_initialization(first_item, output); // operation is always NOT
            commands_pt1.push_back(my_command);
            commands_pt2.push_back(my_command);
        }
        else if(line_items.size() == 5) //binary operation
        {
            string first_item = line_items.front();
            line_items.pop_front();
            string operation = line_items.front();
            line_items.pop_front();
            string second_item = line_items.front();
            line_items.pop_front();
            string output = line_items.back();
            line_items.pop_back();
            my_command.command_initialization(second_item, output, operation, first_item);
            commands_pt1.push_back(my_command);
            commands_pt2.push_back(my_command);
        }
        else //unknown operation
        {
            cout << "Unknown operation: " << line << endl;
            exit(1);
        }
        getline(file, line);

        if(DEBUG && added_command)
        {
            cout << my_command << endl;
        }
    }
    file.close();

    if(DEBUG)
    {
        for(map <string, string>::iterator it = wire_map_pt1.begin(); it != wire_map_pt1.end(); it++)
        {
            cout << it->first << ":" << it->second << endl;
        }
    }

    // solve part 1
    string ret_val = solve_mappings(&wire_map_pt1, &commands_pt1);
    cout << "Answer to part 1 is " << ret_val << endl;
    if(DEBUG)
    {
        for(map <string, string>::iterator it = wire_map_pt1.begin(); it != wire_map_pt1.end(); it++)
        {
            cout << it->first << ":" << it->second << endl;
        }
    }

    // solve part 2
    wire_map_pt2["b"] = ret_val;
    ret_val = solve_mappings(&wire_map_pt2, &commands_pt2);
    cout << "Answer to part 2 is " << ret_val << endl;
}
