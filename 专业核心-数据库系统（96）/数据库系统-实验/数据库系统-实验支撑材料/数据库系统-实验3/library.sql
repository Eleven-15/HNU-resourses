/*==============================================================*/
/* DBMS name:      MySQL 5.0                                    */
/* Created on:     2023/12/12 21:41:42                          */
/*==============================================================*/


drop table if exists admin;

drop table if exists book;

drop table if exists book_reader;

drop table if exists book_visitor;

drop table if exists library;

drop table if exists press;

drop table if exists reader;

drop table if exists visitor;

/*==============================================================*/
/* Table: admin                                                 */
/*==============================================================*/
create table admin
(
   admin_id             char(12) not null,
   admin_name           varchar(30) not null,
   admin_sex            char(2) not null,
   admin_tel            varchar(11) not null,
   admin_email          varchar(50) not null,
   admin_registerdate   date not null,
   admin_pos            varchar(30) not null,
   primary key (admin_id)
);

/*==============================================================*/
/* Table: book                                                  */
/*==============================================================*/
create table book
(
   book_id              char(50) not null,
   press_id             char(5),
   admin_id             char(12),
   library_id           char(5),
   book_name            varchar(50) not null,
   book_writer          varchar(30) not null,
   book_pressid         char(5) not null,
   book_pressdate       date not null,
   book_isbn            char(17) not null,
   book_price           float not null,
   book_copynum         int not null,
   primary key (book_id)
);

/*==============================================================*/
/* Table: book_reader                                           */
/*==============================================================*/
create table book_reader
(
   book_id              char(50) not null,
   reader_id            char(12) not null,
   borrow_date          date not null,
   borrow_expect_returndate date not null,
   borrow_ifrenew       char(1) not null,
   borrow_ifreturn      char(1) not null,
   borrow_returndate    date,
   borrow_time          time not null,
   borrow_terminal      char(3) not null,
   primary key (book_id, reader_id)
);

/*==============================================================*/
/* Table: book_visitor                                          */
/*==============================================================*/
create table book_visitor
(
   vistor_id            char(12) not null,
   book_id              char(50) not null,
   query_time           time not null,
   query_terminal       char(3) not null,
   primary key (vistor_id, book_id)
);

/*==============================================================*/
/* Table: library                                               */
/*==============================================================*/
create table library
(
   library_id           char(5) not null,
   library_name         varchar(30) not null,
   library_tel          char(8) not null,
   library_address      varchar(50) not null,
   primary key (library_id)
);

/*==============================================================*/
/* Table: press                                                 */
/*==============================================================*/
create table press
(
   press_id             char(5) not null,
   press_name           varchar(30) not null,
   press_tel            char(8) not null,
   press_address        varchar(50) not null,
   primary key (press_id)
);

/*==============================================================*/
/* Table: reader                                                */
/*==============================================================*/
create table reader
(
   reader_id            char(12) not null,
   admin_id             char(12),
   reader_name          varchar(30) not null,
   reader_sex           char(2) not null,
   reader_tel           char(11) not null,
   reader_email         varchar(50) not null,
   reader_doc           varchar(30) not null,
   reader_docid         varchar(50) not null,
   reader_registerdate  date not null,
   reader_others        varchar(256),
   primary key (reader_id)
);

/*==============================================================*/
/* Table: visitor                                               */
/*==============================================================*/
create table visitor
(
   vistor_id            char(12) not null,
   admin_id             char(12),
   vistor_registerdate  date not null,
   primary key (vistor_id)
);

alter table book add constraint FK_admin_book foreign key (admin_id)
      references admin (admin_id) on delete restrict on update restrict;

alter table book add constraint FK_book_library foreign key (library_id)
      references library (library_id) on delete restrict on update restrict;

alter table book add constraint FK_book_press foreign key (press_id)
      references press (press_id) on delete restrict on update restrict;

alter table book_reader add constraint FK_book_reader foreign key (book_id)
      references book (book_id) on delete restrict on update restrict;

alter table book_reader add constraint FK_book_reader2 foreign key (reader_id)
      references reader (reader_id) on delete restrict on update restrict;

alter table book_visitor add constraint FK_book_visitor foreign key (vistor_id)
      references visitor (vistor_id) on delete restrict on update restrict;

alter table book_visitor add constraint FK_book_visitor2 foreign key (book_id)
      references book (book_id) on delete restrict on update restrict;

alter table reader add constraint FK_admin_reader foreign key (admin_id)
      references admin (admin_id) on delete restrict on update restrict;

alter table visitor add constraint FK_admin_visitor foreign key (admin_id)
      references admin (admin_id) on delete restrict on update restrict;

