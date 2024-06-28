static void	define_symbol_len(int *len, char index1, char index2)
{
	*len = 1;
	if ((index1 == '<' && index2 == '<') || (index1 == '>' && index2 == '>')
		|| (index1 == '|' && index2))
		*len = 2;
}

void allocate_and_copy_token(char **tokens, int token_count, const char *str, int i, int *c)
{
	tokens[token_count] = malloc((c[1] + 1) * sizeof(char));
	ft_strlcpy(tokens[token_count], &str[i], c[1] + 1);
	tokens[token_count][c[1]] = '\0';
}
	// c[0] = int		symbol_len;
	// c[1] = int		word_len;


char	**tokenize_special_symbols(const char *str, int i, int token_count)
{
	char	**tokens;
	int		c[2];
	int		len;
	int		start;

	if (!(tokens = (len = ft_strlen(str), ft_calloc(100, sizeof(char *)))))
		return (NULL);
	while (i < len && ++token_count <= 1000)
	{
		if (ft_is_special_symbol(str[i]))
		{
			define_symbol_len(&c[0], str[i], str[i + 1]);
			allocate_and_copy_token(tokens, token_count, str, i, c);
			i += c[0];
		}
		else
		{
			start = i;
			while (i < len && !ft_is_space(str[i]) && !ft_is_special_symbol(str[i]))
				i++;
			c[1] = i - start;
			allocate_and_copy_token(tokens, token_count, str, start, c);
		}
	}
	return (tokens);
}


int	init_tokenize_input_vars(char ***tempTokenArray, \
	char ***specialSymbolArray, char ***expandedArray, char ***tokenizedInput)
{
	*tempTokenArray = NULL;
	*specialSymbolArray = NULL;
	*expandedArray = NULL;
	*tokenizedInput = NULL;
	return(-1);
}
void add_special_row(char ***tempTokenArray, char *specialSymbolArray, int *i)
{
	*tempTokenArray = ft_add_row_2d_array(*tempTokenArray, specialSymbolArray);
	*i += 1;
}

char	**tokenize_input(char *input, t_mini **mini)
{
	char	**tokenizedInput;
	char	**expandedArray;
	char	**tempTokenArray;
	char	**specialSymbolArray;
	int		i[2];

	i[0] = init_tokenize_input_vars(&tempTokenArray, &specialSymbolArray, &expandedArray, &tokenizedInput);
	tokenizedInput = split_by_spaces(input, ft_word_count_quotes(ft_strtrim(input, " ")));
	expandedArray = expand_vars(tokenizedInput, mini);
	while (expandedArray[++i[0]])
	{
		if (ft_1st_char_in_set_i(expandedArray[i[0]], "<>|") != -1 && !ft_is_only_special(expandedArray[i[0]]) )
		{
			specialSymbolArray = NULL;
			specialSymbolArray = ft_splice_2d_array(specialSymbolArray,
					tokenize_special_symbols(expandedArray[i[0]], 0, -1), ft_2d_array_len(specialSymbolArray));
			i[1] = -1;
			while (specialSymbolArray[++i[1]])
				add_special_row(&tempTokenArray, specialSymbolArray[i[1]], &i[0]);
			i[0] -= 2;
		}
		else
			tempTokenArray = ft_add_row_2d_array(tempTokenArray, expandedArray[i[0]]);
	}
	ft_free_2d_array(&specialSymbolArray);
	return (ft_add_row_2d_array(tempTokenArray, NULL));
}
