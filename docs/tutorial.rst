Getting Started With Unittest
=============================

This tutorial will walk you through the basics of using MNMLSTC Unittest. It
will introduce to you the concepts that MNMLSTC Unittest introduces, as well
as explain *why* MNMLSTC Unittest works in the way it does.

It should be noted, MNMLSTC Unittest assumes the following:

 * You are using CMake
 * You are using CTest as the test runner
 * You are using a C++11 compiler
 * Any code that interacts with MNMLSTC Unittest will have exceptions enabled

Concepts
--------

Unittest differs from most unit testing libraries in their naming conventions.
This section will discuss how these naming conventions result in a few
*technical* conceptual differences. At the end of the day, however, they are
all the same. You have cases, suites, tests, and fixtures. When explaining the
differences, similarities to other frameworks (such as GTest, Unity, or
python's unittest module) will be made.

.. glossary::

   test suite
    For unittest, the resulting executable produced from CMake is your test
    suite. One could argue that organizing suites within suites ad infinitum is
    unnecessary. This is an argument that MNMLSTC Unittest makes.

   test case
    Unlike python's unittest or GTest, the 'test case' in MNMLSTC Unittest is
    just a 'test'. Tests are made up of steps, or tasks. A case, technically
    speaking, is a collection of steps taken to ensure that your code is
    sane. So, while other systems refer to a collection of tasks as a test
    case, MNMLSTC Unittest calls these a test.

   test step
    A step is placed within a test. They can fail, pass, or skip. They are,
    outside of a single assertion statement, the smallest unit of execution
    within MNMLSTC Unittest, and where most of your work will go.

As you can see from the *very* brief explanations, MNMLSTC Unittest doesn't
differ much from other unit testing libraries. However, in the realm of C++,
it does differ in one major way: *There are absolutely no preprocessor macros*.
But why would MNMLSTC Unittest have none of these?

When it comes to the preprocessor macros, one has to understand what these
macros actually do to understand any potential compiler errors. And at runtime,
we aren't given an idea of *why* the assertion failed (e.g., what are the
values inside of the tested variables, rather than what their names are/what
line it all happens on?). Python's unittest does this well (and it comes as a
result of its ability to perform runtime reflection on variables, as well as
know the current line), but C++ is not python, no matter how hard one wished
it was. As such, MNMLSTC Unittest makes due with what it can.

Your First Unittest Unit Test
-----------------------------

Well, enough about the concepts of Unittest. It's time to write our first
test!

.. todo:: Discuss how unittest is intended to be installed (e.g.,
          an install(EXPORT ...) target might be used in the CMakeLists.txt
          file

.. highlight:: cpp

Because of how MNMLSTC Unittest works, we can declare any test anywhere within
the program, as long as it is within the scope of *some* function. For the
purposes of this tutorial, we'll simply place everything within main::

    #include <unittest/unittest.hpp>

    int main () {
      using namespace unittest;

      test("my-first-test") = {
        task("first-task") = []{ self.fail("Not Yet Implemented"); },
        task("second-task") = []{ self.fail("Not Yet Implemented"); }
      };

      run();
    }

And now, a brief explanation of just what in tarnation we think we're doing
here. First, we include the unittest amalgamation header. This header is
provided to insure that the proper namespaces and declarations are available
for the user.

Next, we do a ``using namespace unittest``. This is *absolutely* vital, as it
allows unittest to use its automatic value printing fallback without issue.

Now to get to the meat of the program. We declare a test with the name
"my-first-test". All tests (and tasks!) *should* use a string literal. However,
as of right now, their interface is to take a ``const char*``. Just don't make
it a ``nullptr``.

On the same line, we begin to assign an initialization_list of tasks. Just know
that the only way to submit tasks to a test case is to place them within
this initialization_list.

Tasks work almost like tests in that we assign a value to them after their
declaration. In the case of a task, it *always* takes a
``std::function<void()>`` by rvalue reference. This means anything you pass
into will not be used elsewhere. At that point, MNMLSTC Unittest now *owns*
that object and will do with it as it pleases. While it is possible to
construct a ``std::function<void()>`` with a variety of ways, it is easiest
to simply use a lambda. The lambda will allow for capturing fixtures (declared
with RAII) by value or by reference. Finally, because we really have nothing
to do, *yet*, we call ``self.fail`` which will immediately make the test
runner stop handling the task.

Finally we call ``run()``, which is located in the unittest namespace.

.. note:: Make sure that this is the last function call you make. Whether 
          all tests and tasks pass or not is irrelevant, as it will *always*
          call ``std::exit``.
