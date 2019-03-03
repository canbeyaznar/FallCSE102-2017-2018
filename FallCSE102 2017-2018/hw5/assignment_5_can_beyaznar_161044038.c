#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_OF_LETTERS ('z' - 'a' + 1) /* Plus one for space character */
#define MAX_COUNT_OF_BI_GRAM ((NUM_OF_LETTERS * NUM_OF_LETTERS) - 1) /* Minus one for double space */
#define VALID      0
#define NOT_VALID -1

#define FOUND      0
#define NOT_FOUND -1

#define FILE_NOT_READ(fp,message) if(NULL == fp) { printf(message); return; }
typedef struct
{
	unsigned char element[2];
	size_t hit_counter;
	double frequency;
}bigram_s;

typedef struct
{
	size_t num_of_bigrams;
	bigram_s list_of_bigrams[MAX_COUNT_OF_BI_GRAM];
	FILE *file_desc;
}language_s;

int is_bigram_valid(bigram_s *p_bigram);
void add_new_bigram_to_list(bigram_s *p_current, bigram_s *p_list, size_t index_of);
int check_bigram_is_in_list(bigram_s *p_current, bigram_s *p_list);
void calculate_frequency_of_bigrams(bigram_s *p_list, size_t p_num_of_bigrams);
void fill_up_bigram_list(language_s *p_language);
double do_calculation(language_s *, language_s *);
void calculate_dissimilarity(const char *p_first_lang_filename, const char *p_second_lang_filename);




int is_bigram_valid(bigram_s *p_bigram)
{
	/* Double space characters are not allowed */
	if (p_bigram->element[0] == ' ' && p_bigram->element[1] == ' ')
	{
		return NOT_VALID;
	}
	/* Newline characters shouldn't bee not allowed */
	if (p_bigram->element[0] == '\n' || p_bigram->element[1] == '\n')
	{
		return NOT_VALID;
	}
	/* First character should be between a and z or can be space */
	if ((p_bigram->element[0] < 'a' || p_bigram->element[0] > 'z') && p_bigram->element[0] != ' ')
	{
		return NOT_VALID;
	}
	/* Second character should be between a and z or can be space */
	if ((p_bigram->element[1] < 'a' || p_bigram->element[1] > 'z') && p_bigram->element[0] != ' ')
	{
		return NOT_VALID;
	}
	return VALID;
}

void add_new_bigram_to_list(bigram_s *p_current, bigram_s *p_list, size_t index_of)
{
	if (index_of >= MAX_COUNT_OF_BI_GRAM)
	{
		printf("Array index is exceeded\n");
		return;
	}
	memcpy(p_list[index_of].element, p_current->element, sizeof(p_current->element));
	p_list[index_of].hit_counter = 1;
}

int check_bigram_is_in_list(bigram_s *p_current, bigram_s *p_list)
{
	size_t i;
	for (i = 0; i < MAX_COUNT_OF_BI_GRAM; i++)
	{
		if (strncmp((const char *)p_current->element, (const char *)p_list[i].element, sizeof(p_current->element)) == 0)
		{
			p_list[i].hit_counter++;
			return FOUND;
		}
	}
	return NOT_FOUND;
}

void calculate_frequency_of_bigrams(bigram_s *p_list, size_t p_num_of_bigrams)
{
	size_t i;
	for (i = 0; i < p_num_of_bigrams; i++)
	{
		p_list[i].frequency = (double)p_list[i].hit_counter / (double)p_num_of_bigrams;
	}
}

void fill_up_bigram_list(language_s *p_language)
{
	bigram_s current = { 0 };
	while (fread(current.element, sizeof(current.element), 1, p_language->file_desc) > 0)
	{
		int is_valid = is_bigram_valid(&current);
		if (VALID == is_valid)
		{
			int is_in_list = check_bigram_is_in_list(&current, p_language->list_of_bigrams);
			if (NOT_FOUND == is_in_list)
			{
				add_new_bigram_to_list(&current, p_language->list_of_bigrams, p_language->num_of_bigrams);
				p_language->num_of_bigrams++;
			}
		}
		fseek(p_language->file_desc, -1, SEEK_CUR); //Go back one character from current file descriptor
	}
	calculate_frequency_of_bigrams(p_language->list_of_bigrams, p_language->num_of_bigrams);
}

double do_calculation(language_s *p_language_first, language_s *p_language_second)
{
	size_t index = 0;
	size_t index_inner = 0;
	double total_similarity_diff = 0.0;
	double sub_similarity_diff = 0.0;

	for(index = 0; index < p_language_first->num_of_bigrams ; index++)
	{
		sub_similarity_diff = p_language_first->list_of_bigrams[index].frequency;

		for(index_inner = 0; index_inner < p_language_second->num_of_bigrams ; index_inner++)
		{
			/* Search ith gram into second language bigram list */
			/* If found, calculate frequency difference. Otherwise, take value from first language text */
			if(strncmp((const char *)p_language_first->list_of_bigrams[index].element,
				(const char *)p_language_second->list_of_bigrams[index_inner].element,
				strlen((const char *)p_language_first->list_of_bigrams[index].element)) == 0)
			{
				sub_similarity_diff = p_language_first->list_of_bigrams[index].frequency - p_language_second->list_of_bigrams[index_inner].frequency;
				if(sub_similarity_diff < 0 ) 
				{
					/* Absolute value must be calculated if value smaller than zero */
					sub_similarity_diff *= (double)-1.0;
				}
				break;
			}
		}

		total_similarity_diff += sub_similarity_diff;
	}
	return total_similarity_diff;
}

void calculate_dissimilarity(const char *p_first_lang_filename, const char *p_second_lang_filename)
{
	language_s first_lang = { 0 };
	language_s second_lang = { 0 };
	FILE *file_ptr_of_first_language;
	FILE *file_ptr_of_second_language;
	double calc_result;

	file_ptr_of_first_language = fopen(p_first_lang_filename, "r");
	FILE_NOT_READ(file_ptr_of_first_language, "File cannot be read properly\n");

	file_ptr_of_second_language = fopen(p_second_lang_filename, "r");
	FILE_NOT_READ(file_ptr_of_second_language, "File cannot be read properly\n");

	first_lang.file_desc = file_ptr_of_first_language;
	second_lang.file_desc = file_ptr_of_second_language;

	fill_up_bigram_list(&first_lang);
	fill_up_bigram_list(&second_lang);

	calc_result = do_calculation(&first_lang, &second_lang);

	printf("%.5f\n",calc_result,p_first_lang_filename,p_second_lang_filename);

	fclose(file_ptr_of_first_language);
	fclose(file_ptr_of_second_language);
}

int main(int argc, char *argv[])
{
	calculate_dissimilarity("language_x.txt", "language_1.txt");
	calculate_dissimilarity("language_x.txt", "language_2.txt");
	calculate_dissimilarity("language_x.txt", "language_3.txt");
	calculate_dissimilarity("language_x.txt", "language_4.txt");
	calculate_dissimilarity("language_x.txt", "language_5.txt");
	return 0;
}
