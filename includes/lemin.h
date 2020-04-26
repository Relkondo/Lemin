#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define FIRST 0
# define LAST 1

typedef struct		s_pipe
{
	struct s_node	*node;
	int				weight;
	int				passed;
	struct s_pipe	*next;
	struct s_pipe	*reverse;
}					t_pipe;

typedef struct		s_node
{
	char			*pseudo;
	int				cost;
	int				id;
	int				ants;
	intmax_t		x;
	intmax_t		y;
	int				passed;
	int				prev_id;
	int				entry;
	t_pipe			*pipes;
	struct s_node	*next;
}					t_node;

typedef struct		s_farm
{
	t_node			**nodes;
	int				start;
	int				end;
	int				nb_ants;
	int				size;
	double			steps;
	int				max_ways;
}					t_farm;

t_farm				*lm_generate_farm(void);
t_node				*lm_generate_nodes(t_node *end, char **line, int entry);
int					lm_parsing_pipes(t_farm *farm, char *line);
unsigned int		lm_hashing(char *name, int size);
int					lm_nodemap(t_farm *farm, t_node *start);
int					lm_start_parsing(t_farm *farm, char *line);
t_pipe				*lm_init_pipe(t_node *node, t_pipe *opp);
t_node				**lm_index(t_farm *farm);
int					lm_get_nb_ants(char *line);
char				**lm_verif_pipe(char *line);
char				**lm_verif_node1(char *node_line);
void				lm_del_pipes(t_pipe *current_pipe);
void				lm_del_node(t_node **target);
void				lm_del_farm(t_farm *farm);
void				lm_free_ways(t_node ***ways);
int					lm_init_algo(t_farm *farm, t_node **nodes);
int					lm_sb_algo(t_farm *farm, t_node **nodes);
void				lm_bf_algo(t_node **nodes, int size);
int					lm_use_way(t_node **nodes);
t_node				***lm_collect_ways(t_node **nodes, int nb_ways);
double				lm_max_steps(t_farm *farm, t_node ***ways, int nb_ways);
int					lm_duplic_nodes(t_node ***ways);
void				lm_recalc_costs(t_node ***ways);
void				lm_move(t_farm *farm, t_node ***ways, t_node **nodes);
int					lm_solve_one_step(char *end, int ants);





//to delete
void				td_display_nodes(t_node **nodes);
void				display_tab(t_node **nodes, int size);
void				td_display_ways(t_farm *farm, t_node ***ways);
void				td_display_node(t_node *node);
void				td_checker(t_node ***ways, t_node *start, t_node *end);

#endif
