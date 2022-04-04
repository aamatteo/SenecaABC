/* ------------------------------------------------------------------   */
/*      item            : LGlights.cxx
        made by         : matteo
        from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Tue Mar  8 17:47:32 2022
        category        : body file
        description     :
        changes         : Tue Mar  8 17:47:32 2022 first version
        template changes: 030401 RvP Added template creation comment
                          060512 RvP Modified token checking code
                          131224 RvP convert snap.data_size to
                                 snap.getDataSize()
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/


#define LGlights_cxx
// include the definition of the module class
#include "LGlights.hxx"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// include the debug writing header. Warning and error messages
// are on by default, debug and info can be selected by
// uncommenting the respective defines
//#define D_MOD
//#define I_MOD
#include <debug.h>

// include additional files needed for your calculation here

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const LGlights::classname = "l-glights";

// initial condition/trim table
const IncoTable* LGlights::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e.
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<_ThisModule_,double>
//       (REF_MEMBER(&_ThisModule_::i_example))}

    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* LGlights::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<_ThisModule_,TimeSpec>
        (&_ThisModule_::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<_ThisModule_,std::vector<int> >
      (&_ThisModule_::checkTiming), check_timing_description },

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL, "please give a description of this module"} };

  return parameter_table;
}

/*
//key call back
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
// When a user presses the escape key, we set the WindowShouldClose property to true
// closing the application
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
*/

// Shaders
// vertex shader: transforms given coordinates in pixel coordinates (????????)
const GLchar* vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "layout (location = 1) in vec3 vertexColor;\n"
                                   "out vec3 theColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                                   "theColor = vertexColor;\n"
                                   "}\0";
// fragment shader: gives final color to the pixel
const GLchar* fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 daColor;\n"
                                     //" out vec4 color;\n"
                                     "in vec3 theColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "daColor = vec4(theColor, 1.0);\n"
                                     //"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                     "}\n\0";

/*
int LGlights::window_setup() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//  return 0;

  window = glfwCreateWindow(800, 600, "LG lights", nullptr,
                                        nullptr);
  if (window == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);

  glfwSetKeyCallback(window, key_callback);


  // Build and compile our shader program

  // Vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // Check for compile time errors when building the vertex shader
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // Fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // Check for compile time errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // now you link the vertex shader and the fragment shader into a single shader program object: this program links the output of each shader with the
// inputs of the next shader (so vertex to fragment)
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // Check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  // apparently the vertex and fragment shader objects are not of use anymore after the activation of the shader programme so they can be deleted
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);


  // Set up vertex data (and buffer(s)) and attribute pointers
  GLfloat vertices[] = {
          0.2f, 0.4f, 0.0f, // Left
          0.2f, 0.7f, 0.1f,
          0.2f, 0.8f, 0.0f, // Right
          0.2f, 0.7f, 0.1f,
          -0.2f,0.8f, 0.0f,  // To
          0.2f, 0.7f, 0.1f,
          -0.2f,  0.4f, 0.0f, // Top
          0.2f, 0.7f, 0.1f,

          -0.2f, -0.8f, 0.0f, // Left
          0.2f, 0.3f, 0.1f,
          -0.2f, -0.4f, 0.0f, // Right
          0.2f, 0.3f, 0.1f,
          -0.6f,  -0.4f, 0.0f,  // Top
          0.2f, 0.3f, 0.1f,
          -0.6f,  -0.8f, 0.0f,  // Top
          0.2f, 0.3f, 0.1f,

          0.6f, -0.8f, 0.0f, // Left
          0.2f, 0.7f, 0.1f,
          0.6f, -0.4f, 0.0f, // Right
          0.2f, 0.7f, 0.1f,
          0.2f,  -0.4f, 0.0f,  // Top
          0.2f, 0.7f, 0.1f,
          0.2f,  -0.8f, 0.0f, // Top
          0.2f, 0.7f, 0.1f,
  };

  GLuint indices[] = {
          0,1,2,
          0,2,3,

          4,5,6,
          4,6,7,

          8,9,10,
          8,10,11
  };

  GLuint EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1,&EBO);

  // binding buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (char*)(sizeof(float)*3));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
  glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
  return 0;
}

*/


// constructor
LGlights::LGlights(Entity* e, const char* part, const
                       PrioritySpec& ps) :
  SimulationModule(e, classname, part, getMyIncoTable(), 0),
  gear(0.0),
  pilot_input_token(getId(), NameSet(getEntity(), "CitationPilotInput", part), 101),
  control_token(getId(), NameSet(getEntity(), "ControlEvent", part)),
  cb1(this, &_ThisModule_::doCalculation),
  do_calc(getId(), "displays LG lights", &cb1, ps)
{
  do_calc.setTrigger(pilot_input_token);
  //window_setup();
}


bool LGlights::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
  return true;
}

// destructor
LGlights::~LGlights()
{
  // Properly de-allocate all resources once they've outlived their purpose
  //glDeleteVertexArrays(1, &VAO);
  //glDeleteBuffers(1, &VBO);
  // Terminate GLFW, clearing any resources allocated by GLFW.
  //glfwTerminate();


  //glfwTerminate();
}

// as an example, the setTimeSpec function
bool LGlights::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  do_calc.setTimeSpec(ts);
  // or do this with the clock if you have it (don't do both!)
  // myclock.changePeriodAndOffset(ts);

  // do whatever else you need to process this in your model
  // hint: ts.getDtInSeconds()

  // return true if everything is acceptable
  return true;
}

// and the checkTiming function
bool LGlights::checkTiming(const std::vector<int>& i)
{
  if (i.size() == 3) {
    new TimingCheck(do_calc, i[0], i[1], i[2]);
  }
  else if (i.size() == 2) {
    new TimingCheck(do_calc, i[0], i[1]);
  }
  else {
    return false;
  }
  return true;
}

// tell DUECA you are prepared
bool LGlights::isPrepared()
{
  bool res = true;

  // Example checking a token:
  // CHECK_TOKEN(w_somedata);

  // Example checking anything
  // CHECK_CONDITION(myfile.good());
  // CHECK_CONDITION2(sometest, "some test failed");

  CHECK_TOKEN(pilot_input_token);
  CHECK_TOKEN(control_token);

  // return result of checks
  return res;
}

// start the module
void LGlights::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void LGlights::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void LGlights::fillSnapshot(const TimeSpec& ts,
                              Snapshot& snap, bool from_trim)
{
  // The most efficient way of filling a snapshot is with an AmorphStore
  // object.
  AmorphStore s(snap.accessData(), snap.getDataSize());

  if (from_trim) {
    // use packData(s, trim_state_variable1); ... to pack your state into
    // the snapshot
  }
  else {
    // this is a snapshot from the running simulation. Dusime takes care
    // that no other snapshot is taken at the same time, so you can safely
    // pack the data you copied into (or left into) the snapshot state
    // variables in here
    // use packData(s, snapshot_state_variable1); ...
  }
}

// reload from a snapshot. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void LGlights::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
{
  // access the data in the snapshot with an AmorphReStore object
  AmorphReStore s(snap.data, snap.getDataSize());

  // use unPackData(s, real_state_variable1 ); ... to unpack the data
  // from the snapshot.
  // You can safely do this, while snapshot loading is going on the
  // simulation is in HoldCurrent or the activity is stopped.
}

// this routine contains the main simulation process of your module. You
// should read the input channels here, and calculate and write the
// appropriate output
void LGlights::doCalculation(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
    // only repeat the output, do not change the model state




    try
    {
      StreamReader<CitationPilotInput> pint(pilot_input_token, ts);

      gear = pint.data().gear;



    }

    catch(Exception& e)
    {
      W_MOD(getId()<< classname << " caught " << e << " @ " << ts <<
                   " -- reading CitationPilotInput Channel");
    }


    break;
    }



  case SimulationState::Replay:
  case SimulationState::Advance: {
    // access the input
    // example:
    // try {
    //   DataReader<MyInput> u(input_token, ts);
    //   throttle = u.data().throttle;
    //   de = u.data().de; ....
    // }
    // catch(Exception& e) {
    //   // strange, there is no input. Should I try to continue or not?
    // }
    /* The above piece of code shows a block in which you try to catch
       error conditions (exceptions) to handle the case in which the input
       data is lost. This is not always necessary, if you normally do not
       foresee such a condition, and you don t mind being stopped when
       it happens, forget about the try/catch blocks. */

    // do the simulation calculations, one step



    try
    {
      StreamReader<CitationPilotInput> pint(pilot_input_token, ts);

      gear = pint.data().gear;



    }

    catch(Exception& e)
    {
      W_MOD(getId()<< classname << " caught " << e << " @ " << ts <<
                   " -- reading CitationPilotInput Channel");
    }

/*
    // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
    glfwPollEvents();

    // Render
    // Clear the colorbuffer
    glClearColor(0.2f, 0.7f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw our first triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);



    glBindVertexArray(0);



    // Swap the screen buffers
    glfwSwapBuffers(window);
*/

    break;
    }
  default:
    // other states should never be entered for a SimulationModule,
    // HardwareModules on the other hand have more states. Throw an
    // exception if we get here,
    throw CannotHandleState(getId(),GlobalId(), "state unhandled");
  }

  // DUECA applications are data-driven. From the time a module is switched
  // on, it should produce data, so that modules "downstreams" are
  // activated
  // access your output channel(s)
  // example
  // DataWriter<MyOutput> y(output_token, ts);

  // write the output into the output channel, using the stream writer
  // y.data().var1 = something; ...

  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the
    // sendSnapshot routine, later, and possibly at lower priority
    // e.g.
    // snapshot_state_variable1 = state_variable1; ...
    // (or maybe if your state is very large, there is a cleverer way ...)
  }
}

void LGlights::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
{
  // read the event equivalent of the input data
  // example
  // DataReader<MyData> u(i_input_token, ts);

  // using the input, and the data put into your trim variables,
  // calculate the derivative of the state. DO NOT use the state
  // vector of the normal simulation here, because it might be that
  // this is done while the simulation runs!
  // Some elements in this state derivative are needed as target, copy
  // these out again into trim variables (see you TrimTable

  // trim calculation
  switch(mode) {
  case FlightPath: {
    // one type of trim calculation, find a power setting and attitude
    // belonging to a flight path angle and speed
  }
  break;

  case Speed: {
    // find a flightpath belonging to a speed and power setting (also
    // nice for gliders)
  }
  break;

  case Ground: {
    // find an altitude/attitude belonging to standing still on the
    // ground, power/speed 0
  }
  break;

  default:
    W_MOD(getId() << " cannot calculate inco mode " << mode);
  break;
  }

  // This works just like a normal calculation, only you provide the
  // steady state value (if your system is stable anyhow). So, if you
  // have other modules normally depending on your output, you should
  // also produce the equivalent output here.
  // DataWriter<MyOutput> y(output_token, ts);

  // write the output into the output channel, using the DataWriter

  // now return. The real results from the trim calculation, as you
  // specified them in the TrimTable, will now be collected and sent
  // off for processing.
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<LGlights> a(LGlights::getMyParameterTable());

