// FIXME - remove test protos------------------
Rec *rec_alloc();
void rec_free(Rec *rec);
Rec *rec_create_dummy(int k);
int get_type_and_length_dummy(const void *int_hdr, Data_type *type_rtn, size_t *num_words_rtn);
void read_record_data_dummy(size_t nwords, 
			    void *data_return);
int read_record_data_core(int fd, 
			  size_t data_offset, 
			  size_t disk_length, 
			  Byte_ordering byte_ordering, 
			  int word_size, 
			  const void *int_hdr,
			  const void *real_hdr,
			  size_t nwords, 
			  void *data_return);
//-----------------------

/* interpret_header.c */
Data_type get_type(const INTEGER *int_hdr);
size_t get_data_length (const INTEGER *int_hdr);

int get_type_and_length_core(const INTEGER *int_hdr,
			     Data_type *type_rtn,
			     size_t *num_words_rtn);

/* read.c */
void swap_bytes(void *ptr, size_t num_words);
void swapbytes_if_swapped(void *ptr, 
			  size_t num_words,
			  Byte_ordering byte_ordering);
size_t read_words(int fd, 
		  void *ptr,
		  size_t num_words,
		  Byte_ordering byte_ordering);

int read_hdr_at_offset(int fd,
		       size_t header_offset,
		       Byte_ordering byte_ordering, 
		       INTEGER *int_hdr_rtn,
		       REAL *real_hdr_rtn);

int read_hdr(int fd,
	     Byte_ordering byte_ordering, 
	     INTEGER *int_hdr_rtn,
	     REAL *real_hdr_rtn);

Rec *get_record(File *file, List *heaplist);
int read_all_headers(File *file, List *heaplist);
size_t skip_fortran_record(File *file);
int skip_word(File *file);
int read_all_headers_pp(File *file, List *heaplist);
int read_all_headers_ff(File *file, List *heaplist);
int get_ff_disk_length(INTEGER *ihdr);
int get_valid_records_ff(int fd,
			 Byte_ordering byte_ordering,
			 size_t hdr_start, size_t hdr_size, int nrec,
			 int valid[], int *n_valid_rec_return);

/* process_vars.c */
int process_vars(File *file, List *heaplist);
int initialise_records(Rec **recs, int nrec, List *heaplist);

/* level.c */
int lev_set(Level *lev, const Rec *rec);
Lev_type level_type(const Rec *rec);

/* date_and_time.c */
REAL mean_period(const Time *time);
int is_time_mean(INTEGER LBTIM);
REAL time_diff(INTEGER lbtim, const Date *date, const Date *orig_date);
REAL sec_to_day(int8 seconds);
Calendar_type calendar_type(INTEGER type);
int8 gregorian_to_secs(const Date *date);
int time_set(Time *time, const Rec *rec);

/* compare.c */
int compare_records_between_vars(const Rec *a, const Rec *b);
int compare_mean_periods(const Rec *a, const Rec *b);
int compare_records_within_var(const Rec *a, const Rec *b);
int compare_records(const void *p1, const void *p2);
int records_from_different_vars(const Rec *a, const Rec *b);
int compare_lists(const List *l1, const List *l2, int (*compfunc)(const void*, const void*));
int compare_levels(const void *p1, const void *p2);
int compare_zaxes(const void *p1, const void *p2);
int compare_times(const void *p1, const void *p2);
int compare_dates(const Date *a, const Date *b);
int compare_taxes(const void *p1, const void *p2);


/* Debug_dump.c */
void debug_dump_all_headers(File *file);

#ifdef MAIN
int main();
#endif