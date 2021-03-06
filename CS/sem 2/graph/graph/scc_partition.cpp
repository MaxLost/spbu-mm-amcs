#include "scc_partition.h"

int form_order(graph* g, int v, int *status, int* order) {
	status[v] = 1;
	node *arc_ptr = find_adj_node(v, g)->arc_list;
	while (arc_ptr) {
		if (status[arc_ptr->num] == 0) {
			form_order(g, arc_ptr->num, status, order);
		}
		arc_ptr = arc_ptr->next;
	}
	while (*order != -1) {
		++order;
	}
	*order = v;
	return 0;
}

int find_components(graph* h, int v, int* status, int component, int* parts) {
	status[v] = 1;
	parts[v] = component;
	node* arc_ptr = find_adj_node(v, h)->arc_list;
	while (arc_ptr) {
		if (status[arc_ptr->num] == 0) {
			find_components(h, arc_ptr->num, status, component, parts);
		}
		arc_ptr = arc_ptr->next;
	}
	return 0;
}

graph* invert_arcs(graph* g) {
	graph* result = graph_init(g->n);
	adj_node* adj_ptr = g->adj_list;
	while (adj_ptr) {
		node* arc_ptr = adj_ptr->arc_list;
		while (arc_ptr) {
			add_arc(result, arc_ptr->num, adj_ptr->num);
			arc_ptr = arc_ptr->next;
		}
		adj_ptr = adj_ptr->next;
	}
	return result;
}

int scc_partition(graph* g, int* parts) {
	int* status = (int *) calloc(g->n, sizeof(int));
	int* order = (int*) malloc(g->n * sizeof(int));
	
	if (!order || !status) return 1;
	
	for (int i = 0; i < g->n; i++) {
		order[i] = -1;
		parts[i] = -1;
	}
	
	graph* h = invert_arcs(g);

	for (int i = 0; i < g->n; i++) {
		if (!status[i]) {
			form_order(g, i, status, order);
		}
	}

	for (int i = 0; i < g->n; i++) status[i] = 0;

	int component = 0;
	for (int i = h->n - 1; i >= 0; i--) {
		int v = order[i];
		if (!status[v]) {
			find_components(h, v, status, component, parts);
			component++;
		}
	}
	graph_free(h);
	return 0;
}

int tarjan_scc_dfs(graph* g, int v, node **stack, int *components, int *status) {
	status[v] = v + 1;
	components[v] = v + 1;
	node* arc_ptr = find_adj_node(v, g)->arc_list;
	while (arc_ptr) {
		if (status[arc_ptr->num]) {
			components[v] = MIN(components[v], components[arc_ptr->num]);
			if (components[arc_ptr->num] == status[arc_ptr->num]) {
				while (*stack) {
					int x = stack_pop(stack);
					components[x] = components[v];
				}
			}
		}
		else {
			stack_push(stack, arc_ptr->num);
			tarjan_scc_dfs(g, arc_ptr->num, stack, components, status);
		}
		arc_ptr = arc_ptr->next;
	}
	return 0;
}

int tarjan_scc(graph* g, int* components) {
	int* status = (int*)calloc(g->n, sizeof(int));
	if (!components || !status) {
		return 1;
	}
	for (int i = 0; i < g->n; i++) components[i] = -1;
	
	for (int i = 0; i < g->n; i++) {
		if (!status[i]) {
			node* stack = create_node(i);
			int state = tarjan_scc_dfs(g, i, &stack, components, status);
			if (state) {
				list_free(&stack);
				return 1;
			}
		}
	}
	free(status);
	return 0;
}
