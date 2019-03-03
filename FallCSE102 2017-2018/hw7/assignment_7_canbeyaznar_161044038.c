#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LABEL_STR_LENGTH 32

#define INVALID_INPUT_VALUE  0xFF
#define INVALID_OUTPUT_VALUE 0xFE

unsigned int former_out = 0;

static int is_all_logic_gates_created = 0;

typedef enum operand_t
{
	AND_GATE = 0,
	NOT_GATE,
	OR_GATE,
	FLIPFLOP_GATE
}operand_e;

typedef struct input_t
{
	char label[MAX_LABEL_STR_LENGTH];
	unsigned int value;
	struct input_t *next;
}input_s;

typedef struct logic_gate_t
{
	char label[MAX_LABEL_STR_LENGTH];
	operand_e operand_type;
	unsigned int input1;
	unsigned int input2;
	unsigned int result;
	struct logic_gate_t *next;
}logic_gate_s;

void create_new_logic_gate(logic_gate_s *logic_gate_ptr, logic_gate_s **head)
{
	logic_gate_s *current = NULL;
	logic_gate_s *new_logic_gate = (logic_gate_s *)malloc(sizeof(logic_gate_s));

	if (NULL == new_logic_gate)
	{
		printf("Unexpected failure! Malloc failed\n");
		return;
	}
	if (NULL == logic_gate_ptr)
	{
		printf("Unexpected parameter value! Label should contain at least one character!\n");
		free(new_logic_gate);
		return;
	}

	strcpy(new_logic_gate->label,logic_gate_ptr->label);
	new_logic_gate->operand_type = logic_gate_ptr->operand_type;
	new_logic_gate->input1 = logic_gate_ptr->input1;
	new_logic_gate->input2 = logic_gate_ptr->input2;
	new_logic_gate->result = logic_gate_ptr->result;
	new_logic_gate->next   = NULL;

	if (*head == NULL)
	{
		*head = new_logic_gate;
	}
	else
	{
		current = *head;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_logic_gate;
	}
}

void delete_all_logic_gates(logic_gate_s **head)
{
	logic_gate_s *curr = *head;
	while (curr)
	{
		*head = curr->next;
		free(curr);
		curr = *head;
	}
	curr = NULL;
}

void create_new_input(const char* param_label, unsigned int param_value, input_s **head)
{
	input_s *current = NULL;
	input_s *new_input = (input_s *)malloc(sizeof(input_s));

	if (NULL == new_input)
	{
		printf("Unexpected failure! Malloc failed\n");
		return;
	}
	if (NULL == param_label)
	{
		printf("Unexpected parameter value! Label should contain at least one character!\n");
		free(new_input);
		return;
	}

	strcpy(new_input->label, param_label);
	new_input->value = param_value;
	new_input->next = NULL;

	if (*head == NULL)
	{
		*head = new_input;
	}
	else
	{
		current = *head;
		while (current->next)
		{
			if (strcmp(current->label, param_label) == 0)
			{
				// If new label is already defined, no need to add again!
				free(new_input);
				return;
			}
			current = current->next;
		}
		current->next = new_input;
	}
}

void delete_all_inputs(input_s **head)
{
	input_s *curr = *head;
	while (curr)
	{
		*head = curr->next;
		free(curr);
		curr = *head;
	}
	curr = NULL;
}

unsigned int get_input_value(input_s *head, const char *p_search_name)
{
	input_s *curr = head;
	while (curr)
	{
		if (strcmp(p_search_name, curr->label) == 0)
		{
			return curr->value;
		}
		curr = curr->next;
	}
	//If label cannot be found on inputs, it can be logic gate name
	return INVALID_INPUT_VALUE;
}

unsigned int get_logic_gate_output_value(logic_gate_s **logic_gate_head, const char *p_search_name)
{
	logic_gate_s *curr = *logic_gate_head;
	while (curr)
	{
		if (strcmp(p_search_name, curr->label) == 0)
		{
			return curr->result;
		}
		curr = curr->next;
	}
	// Unexpected error! At least name should be found on logic gates
	return INVALID_OUTPUT_VALUE;
}

void calculate_logic_operation(logic_gate_s *logic_gate_ptr)
{
	switch (logic_gate_ptr->operand_type)
	{
		case AND_GATE:
			logic_gate_ptr->result = logic_gate_ptr->input1 && logic_gate_ptr->input2;
			break;
		case NOT_GATE:
			logic_gate_ptr->result = (logic_gate_ptr->input1 == 0) ? 1 : 0;
			break;
		case OR_GATE:
			logic_gate_ptr->result = logic_gate_ptr->input1 || logic_gate_ptr->input2;
			break;
		case FLIPFLOP_GATE:
			logic_gate_ptr->result = (logic_gate_ptr->input1 == former_out) ? 1 : 0;
			break;
		default:
			break;
	};
}

void set_operand_type(logic_gate_s *logic_gate_ptr,const char *operand_name)
{
	if (strcmp(operand_name, "AND") == 0)
	{
		logic_gate_ptr->operand_type = AND_GATE;
	}
	else if (strcmp(operand_name, "OR") == 0)
	{
		logic_gate_ptr->operand_type = OR_GATE;
	}
	else if (strcmp(operand_name, "NOT") == 0)
	{
		logic_gate_ptr->operand_type = NOT_GATE;
	}
	else if (strcmp(operand_name, "FLIPFLOP") == 0)
	{
		logic_gate_ptr->operand_type = FLIPFLOP_GATE;
	}
	else
	{
		printf("Expected logic gate type!\n");
	}
}

void set_input_logic_gate_values(logic_gate_s *logic_gate_ptr, input_s *input_head_ptr, logic_gate_s **logic_gate_head, char *param_line)
{
	char delim[2] = " ";
	char *token = strtok(param_line, delim);
	if (NULL != token)
	{
		set_operand_type(logic_gate_ptr, token);
	}
	token = strtok(NULL, delim);
	if (NULL != token)
	{
		strcpy(logic_gate_ptr->label, token);
	}
	token = strtok(NULL, delim);
	if (NULL != token)
	{
		logic_gate_ptr->input1 = get_input_value(input_head_ptr, token);
		if (logic_gate_ptr->input1 == INVALID_INPUT_VALUE)
		{
			logic_gate_ptr->input1 = get_logic_gate_output_value(logic_gate_head, token);
		}
	}
	token = strtok(NULL, delim);
	if (NULL != token)
	{
		logic_gate_ptr->input2 = get_input_value(input_head_ptr, token);
		if (logic_gate_ptr->input2 == INVALID_INPUT_VALUE)
		{
			logic_gate_ptr->input2 = get_logic_gate_output_value(logic_gate_head, token);
		}
	}
	calculate_logic_operation(logic_gate_ptr);
}

unsigned int prepare_final_result(logic_gate_s *logic_gate_head)
{
	logic_gate_s *curr = logic_gate_head;
	while (curr->next)
	{
		curr = curr->next;
	}
	return curr->result;
}

void find_input_line_from_circuit(FILE *fp_circuit_ptr, char *line,unsigned int line_length)
{
	while (fgets(line, line_length, fp_circuit_ptr))
	{
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = 0;      // Escape from newline character

		if (strstr(line, "INPUT") != NULL)
			break;
	}
}

void assign_labels_to_inputs(FILE *fp_circuit_ptr, input_s **input_head)
{
	char delim[2] = " ";
	char line[256] = { 0 };

	find_input_line_from_circuit(fp_circuit_ptr, line,sizeof(line));

	char *token = strtok(line, delim);

	while (token != NULL) 
	{
		if (strcmp("INPUT", token) == 0) {}
		else
		{
			create_new_input(token, 0, input_head);
		}
		token = strtok(NULL, delim);
	}
}

void set_input_values(FILE *fp_input_ptr, input_s *input_head)
{
	unsigned int temp_value = 0;
	input_s *curr = input_head;
	while (curr)
	{
		fscanf(fp_input_ptr, "%d", &temp_value);
		curr->value = temp_value;
		curr = curr->next;
	}
}

void cleanup_input_values(input_s *input_head)
{
	input_s *curr = input_head;
	while (curr)
	{
		curr->value = 0;
		curr = curr->next;
	}
}

void cleanup_logic_gate_output_values(logic_gate_s *logic_gate_head)
{
	logic_gate_s *curr = logic_gate_head;
	while (curr)
	{
		curr->input1 = curr->input2 = curr->result = 0;
		curr = curr->next;
	}
}

void execute_inputs_on_gates(FILE *fp_circuit_ptr, input_s *input_head, logic_gate_s **logic_gate_head)
{
	char line[256] = { 0 };

	while (fgets(line, sizeof(line), fp_circuit_ptr)) 
	{
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = 0;      // Escape from newline character

		if (strstr(line, "INPUT") == NULL)
		{
			logic_gate_s temp_logic_gate = { 0 };
			
			set_input_logic_gate_values(&temp_logic_gate, input_head, logic_gate_head, line);

			// After creation of the logic gates, no need to create again. // Use static guard for it.
			if (0 == is_all_logic_gates_created)
			{
				create_new_logic_gate(&temp_logic_gate, logic_gate_head);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	unsigned int out_result = 0;
	input_s *inputs = NULL;
	logic_gate_s *logic_gates = NULL;
	FILE *fp_input = fopen("input.txt", "r");
	if (NULL == fp_input)
	{
		printf("File cannot be read!\n");
		return -1;
	}

	FILE *fp_circuit = fopen("circuit.txt", "r");
	if (NULL == fp_circuit)
	{
		printf("File cannot be read!\n");
		return -1;
	}

	FILE *fp_output = fopen("output.txt", "w");
	if (NULL == fp_output)
	{
		printf("File cannot be written!\n");
		return -1;
	}

	// Assign label names to inputs from circuit.txt
	assign_labels_to_inputs(fp_circuit,&inputs);

	while (!feof(fp_input))
	{
		set_input_values(fp_input, inputs);
		execute_inputs_on_gates(fp_circuit, inputs, &logic_gates);
		is_all_logic_gates_created = 1;
		out_result = prepare_final_result(logic_gates);
		fprintf(fp_output, "%d\n", out_result);
		former_out = out_result;
		cleanup_input_values(inputs);
		cleanup_logic_gate_output_values(logic_gates);
	}

	// Dynamic allocations must be given back to system!
	delete_all_inputs(&inputs);
	delete_all_logic_gates(&logic_gates);

	fclose(fp_input);
	fclose(fp_circuit);
	fclose(fp_output);

	// To be on safe side, all pointers must be assigned to NULL.
	inputs = NULL;
	logic_gates = NULL;

	return 0;
}